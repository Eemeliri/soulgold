#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
#include "field_specials.h"
#include "fieldmap.h"
#include "malloc.h"
#include "overworld.h"
#include "random.h"
#include "script_movement.h"
#include "script.h"
#include "sound.h"
#include "constants/event_objects.h"
#include "constants/songs.h"

#pragma GCC optimize("O3")

#define PATH_FINDER_WEIGHT 1.5
#define PATH_FINDER_MAX_ELEVATION 15

struct PathNode
{
    struct PathNode *parent;
    u32 costG;
    u32 costF;
    s16 x;
    s16 y;
    u8 elevation;
    u8 move;
};

// Priority queue used to
// pick the next node to explore.
struct PathQueue
{
    struct PathNode **nodes;
    u32 capacity;
    u32 size;
};

// Unordered set for storing
// already explored nodes.
struct PathList
{
    struct PathNode **nodes;
    u32 capacity; // is always a power of 2.
    u32 mask; // is always: capacity - 1.
    u32 size;
};

struct PathFinderContext
{
    struct PathQueue nodeFrontier;
    struct PathList exploredNodes;
    struct Coords16 start;
    struct Coords16 target;
    struct ObjectEvent *objectEvent;
    struct PathNode *nodeBuffer;
    u32 nodeCount;
    u32 speed;
    u32 maxNodes;
    u8 facingDirection;
};

static u8 *FindPathForObjectEvent(struct PathFinderContext *ctx, u32 maxNodes);
static void MoveObjectEventToCoords(u8 localId, s16 targetX, s16 targetY, u8 facingDirection, u32 speed, u32 maxNodes);
static u8 *ReconstructPath(struct PathNode *targetNode, u8 facingDirection);
static inline bool32 PathFinderTargetReached(struct PathFinderContext *ctx, struct PathNode *node);
static inline u32 ManhattanDistance(s16 x1, s16 y1, s16 x2, s16 y2);
static u8 CheckForPathFinderCollision(struct ObjectEvent *objectEvent, struct PathNode *node, s16 x, s16 y, u8 direction);
static inline void TryCreateNeighbor(struct PathFinderContext *ctx, struct PathNode *currentNode, u8 direction);

static inline struct PathNode *PathNode_Create(struct PathFinderContext *ctx, s16 x, s16 y, u32 costG, struct PathNode *parent);
static inline u8 PathNode_GetElevation(struct PathNode *node, s16 x, s16 y);
static inline bool32 PathNode_HasLowerCost(struct PathNode *node1, struct PathNode *node2);
static inline bool32 PathNode_Equal(struct PathNode *node1, struct PathNode *node2);
static inline u32 PathNode_Hash(struct PathNode *node);

static struct PathQueue PathQueue_Create(u32 capacity);
static void PathQueue_Destroy(struct PathQueue *queue);
static bool32 PathQueue_Push(struct PathQueue *queue, struct PathNode *node);
static bool32 PathQueue_Pop(struct PathQueue *queue, struct PathNode **outNode);
static inline void PathQueue_HeapifyUp(struct PathQueue *queue, u32 index);
static inline void PathQueue_HeapifyDown(struct PathQueue *queue, u32 index);

static struct PathList PathList_Create(u32 capacity);
static void PathList_Destroy(struct PathList *list);
static bool32 PathList_TryInset(struct PathList *list, struct PathNode *node, struct PathNode **out);
static bool32 PathList_HasNode(struct PathList *list, struct PathNode *node);

static const u8 sNeighbors[] =
{
    DIR_SOUTH,
    DIR_NORTH,
    DIR_WEST,
    DIR_EAST,
};

// Based on the Manhattan Distance.
static const u8 sPrecomputedDistance[] =
{
    [DIR_NONE] = 0,
    [DIR_SOUTH] = 1,
    [DIR_NORTH] = 1,
    [DIR_WEST] = 1,
    [DIR_EAST] = 1,
    [DIR_SOUTHWEST] = 2,
    [DIR_SOUTHEAST] = 2,
    [DIR_NORTHWEST] = 2,
    [DIR_NORTHEAST] = 2,
};

static const u8 sWalkNormalMovement[] =
{
    [DIR_NONE] = MOVEMENT_ACTION_NONE,
    [DIR_SOUTH] = MOVEMENT_ACTION_WALK_NORMAL_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_WALK_NORMAL_UP,
    [DIR_WEST] = MOVEMENT_ACTION_WALK_NORMAL_LEFT,
    [DIR_EAST] = MOVEMENT_ACTION_WALK_NORMAL_RIGHT,
    [DIR_SOUTHWEST] = MOVEMENT_ACTION_WALK_NORMAL_DIAGONAL_DOWN_LEFT,
    [DIR_SOUTHEAST] = MOVEMENT_ACTION_WALK_NORMAL_DIAGONAL_DOWN_RIGHT,
    [DIR_NORTHWEST] = MOVEMENT_ACTION_WALK_NORMAL_DIAGONAL_UP_LEFT,
    [DIR_NORTHEAST] = MOVEMENT_ACTION_WALK_NORMAL_DIAGONAL_UP_RIGHT,
};

static const u8 sWalkFastMovement[] =
{
    [DIR_NONE] = MOVEMENT_ACTION_NONE,
    [DIR_SOUTH] = MOVEMENT_ACTION_WALK_FAST_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_WALK_FAST_UP,
    [DIR_WEST] = MOVEMENT_ACTION_WALK_FAST_LEFT,
    [DIR_EAST] = MOVEMENT_ACTION_WALK_FAST_RIGHT,
    [DIR_SOUTHWEST] = MOVEMENT_ACTION_WALK_FAST_DIAGONAL_DOWN_LEFT,
    [DIR_SOUTHEAST] = MOVEMENT_ACTION_WALK_FAST_DIAGONAL_DOWN_RIGHT,
    [DIR_NORTHWEST] = MOVEMENT_ACTION_WALK_FAST_DIAGONAL_UP_LEFT,
    [DIR_NORTHEAST] = MOVEMENT_ACTION_WALK_FAST_DIAGONAL_UP_RIGHT,
};

static const u8 sWalkFasterMovement[] =
{
    [DIR_NONE] = MOVEMENT_ACTION_NONE,
    [DIR_SOUTH] = MOVEMENT_ACTION_WALK_FASTER_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_WALK_FASTER_UP,
    [DIR_WEST] = MOVEMENT_ACTION_WALK_FASTER_LEFT,
    [DIR_EAST] = MOVEMENT_ACTION_WALK_FASTER_RIGHT,
    [DIR_SOUTHWEST] = MOVEMENT_ACTION_WALK_FAST_DIAGONAL_DOWN_LEFT,
    [DIR_SOUTHEAST] = MOVEMENT_ACTION_WALK_FAST_DIAGONAL_DOWN_RIGHT,
    [DIR_NORTHWEST] = MOVEMENT_ACTION_WALK_FAST_DIAGONAL_UP_LEFT,
    [DIR_NORTHEAST] = MOVEMENT_ACTION_WALK_FAST_DIAGONAL_UP_RIGHT,
};

static const u8 sWalkSlowMovement[] =
{
    [DIR_NONE] = MOVEMENT_ACTION_NONE,
    [DIR_SOUTH] = MOVEMENT_ACTION_WALK_SLOW_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_WALK_SLOW_UP,
    [DIR_WEST] = MOVEMENT_ACTION_WALK_SLOW_LEFT,
    [DIR_EAST] = MOVEMENT_ACTION_WALK_SLOW_RIGHT,
    [DIR_SOUTHWEST] = MOVEMENT_ACTION_WALK_SLOW_DIAGONAL_DOWN_LEFT,
    [DIR_SOUTHEAST] = MOVEMENT_ACTION_WALK_SLOW_DIAGONAL_DOWN_RIGHT,
    [DIR_NORTHWEST] = MOVEMENT_ACTION_WALK_SLOW_DIAGONAL_UP_LEFT,
    [DIR_NORTHEAST] = MOVEMENT_ACTION_WALK_SLOW_DIAGONAL_UP_RIGHT,
};

static const u8 sJump2Movement[] =
{
    [DIR_NONE] = MOVEMENT_ACTION_NONE,
    [DIR_SOUTH] = MOVEMENT_ACTION_JUMP_2_DOWN,
    [DIR_NORTH] = MOVEMENT_ACTION_JUMP_2_UP,
    [DIR_WEST] = MOVEMENT_ACTION_JUMP_2_LEFT,
    [DIR_EAST] = MOVEMENT_ACTION_JUMP_2_RIGHT,
};

static const u8 sPathFinderFailScript[] =
{
    MOVEMENT_ACTION_EMOTE_X,
    MOVEMENT_ACTION_STEP_END,
};

static const u8* sMovementsBySpeed[] =
{
    sWalkSlowMovement,
    sWalkNormalMovement,
    sWalkFastMovement,
    sWalkFasterMovement,
};

struct PathFinderContext CreatePathFinderContext(struct ObjectEvent *objectEvent, s16 targetX, s16 targetY, u8 facingDirection, u8 speed, u32 maxNodes)
{
    if (speed >= ARRAY_COUNT(sMovementsBySpeed))
        speed = ARRAY_COUNT(sMovementsBySpeed) - 1;

    if (facingDirection > DIR_EAST)
        facingDirection -= DIR_EAST;

    struct PathFinderContext ctx;
    ctx.start.x = objectEvent->currentCoords.x;
    ctx.start.y = objectEvent->currentCoords.y;
    ctx.target.x = targetX + MAP_OFFSET;
    ctx.target.y = targetY + MAP_OFFSET;
    ctx.objectEvent = objectEvent;
    ctx.facingDirection = facingDirection;
    ctx.speed = speed;

    ctx.maxNodes = maxNodes;
    ctx.nodeBuffer = Alloc(sizeof(struct PathNode) * maxNodes);
    ctx.nodeCount = 0;

    ctx.nodeFrontier = PathQueue_Create(maxNodes);
    ctx.exploredNodes = PathList_Create(maxNodes);

    return ctx;
}

void DestroyPathFinderContex(struct PathFinderContext *ctx)
{
    Free(ctx->nodeBuffer);
    PathList_Destroy(&ctx->exploredNodes);
    PathQueue_Destroy(&ctx->nodeFrontier);
    ctx->nodeCount = 0;
}

extern struct ObjectEvent *ScriptHideFollower(void);

void ScrCmd_moveobjecttocoords(struct ScriptContext *ctx)
{
    u16 localId = VarGet(ScriptReadHalfword(ctx));
    u16 x = VarGet(ScriptReadHalfword(ctx));
    u16 y = VarGet(ScriptReadHalfword(ctx));
    u8 facingDirection = VarGet(ScriptReadByte(ctx));
    u8 speed = VarGet(ScriptReadByte(ctx));
    u32 maxNodes = ScriptReadWord(ctx);
    struct ObjectEvent *objEvent;

    Script_RequestEffects(SCREFF_V1 | SCREFF_HARDWARE);

    // When applying script movements to follower, it may have frozen animation that must be cleared
    if ((localId == OBJ_EVENT_ID_FOLLOWER && (objEvent = GetFollowerObject()) && objEvent->frozen) 
            || ((objEvent = &gObjectEvents[GetObjectEventIdByLocalId(localId)]) && IS_OW_MON_OBJ(objEvent)))
    {
        ClearObjectEventMovement(objEvent, &gSprites[objEvent->spriteId]);
        gSprites[objEvent->spriteId].animCmdIndex = 0; // Reset start frame of animation
    }

    MoveObjectEventToCoords(localId, x, y, facingDirection, speed, maxNodes);
    SetMovingNpcId(localId);

    if (localId != OBJ_EVENT_ID_FOLLOWER && !FlagGet(FLAG_SAFE_FOLLOWER_MOVEMENT))
        ScriptHideFollower();
}

static void MoveObjectEventToCoords(u8 localId, s16 targetX, s16 targetY, u8 facingDirection, u32 speed, u32 maxNodes)
{
    struct ObjectEvent *objectEvent = &gObjectEvents[GetObjectEventIdByLocalId(localId)];
    struct PathFinderContext ctx = CreatePathFinderContext(objectEvent, targetX, targetY, facingDirection, speed, maxNodes);

    const u8 *movementScript = FindPathForObjectEvent(&ctx, maxNodes);
    if (movementScript == NULL)
    {
        PlaySE(SE_PIN);
        movementScript = sPathFinderFailScript;
    }

    DestroyPathFinderContex(&ctx);

    objectEvent->directionOverwrite = DIR_NONE;
    ScriptMovement_StartObjectMovementScript(localId, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup, movementScript);
}

static u8 *FindPathForObjectEvent(struct PathFinderContext *ctx, u32 maxNodes)
{
    if (maxNodes == 0)
        return NULL;

    struct PathNode *startNode = PathNode_Create(ctx, ctx->start.x, ctx->start.y, 0, NULL);
    startNode->elevation = ctx->objectEvent->currentElevation;
    ctx->nodeCount++;

    PathQueue_Push(&ctx->nodeFrontier, startNode);
    struct PathNode *nextNode;

    while (PathQueue_Pop(&ctx->nodeFrontier, &nextNode))
    {
        struct PathNode *currentNode = NULL;
        bool32 inserted = PathList_TryInset(&ctx->exploredNodes, nextNode, &currentNode);
        if (inserted == FALSE)
            continue;

        if (PathFinderTargetReached(ctx, currentNode))
            return ReconstructPath(currentNode, ctx->facingDirection);

        for (u32 i = 0; i < ARRAY_COUNT(sNeighbors); i++)
            TryCreateNeighbor(ctx, currentNode, sNeighbors[i]);
    }

    return NULL;
}

static inline void TryCreateNeighbor(struct PathFinderContext *ctx, struct PathNode *currentNode, u8 direction)
{
    s16 neighborX = currentNode->x + gDirectionToVectors[direction].x;
    s16 neighborY = currentNode->y + gDirectionToVectors[direction].y;
    u8 collision = CheckForPathFinderCollision(ctx->objectEvent, currentNode, neighborX, neighborY, direction);

    struct PathNode *neighbor = NULL;

    if (collision == COLLISION_NONE)
    {
        if (ctx->objectEvent->directionOverwrite != DIR_NONE)
        {
            direction = ctx->objectEvent->directionOverwrite;
            neighborX = currentNode->x + gDirectionToVectors[direction].x;
            neighborY = currentNode->y + gDirectionToVectors[direction].y;
        }

        u32 tentativeG = currentNode->costG + sPrecomputedDistance[direction];

        neighbor = PathNode_Create(ctx, neighborX, neighborY, tentativeG, currentNode);
        if (neighbor == NULL)
            return;

        if (PathList_HasNode(&ctx->exploredNodes, neighbor))
            return;

        neighbor->move = sMovementsBySpeed[ctx->speed][direction];
    }
    else if (collision == COLLISION_LEDGE_JUMP)
    {
        neighborX = currentNode->x + gDirectionToVectors[direction].x * 2;
        neighborY = currentNode->y + gDirectionToVectors[direction].y * 2;

        u32 tentativeG = currentNode->costG + sPrecomputedDistance[direction] * 2;

        neighbor = PathNode_Create(ctx, neighborX, neighborY, tentativeG, currentNode);
        if (neighbor == NULL)
            return;

        if (PathList_HasNode(&ctx->exploredNodes, neighbor))
            return;

        neighbor->move = sJump2Movement[direction];
    }
    else
    {
        return;
    }

    if (PathQueue_Push(&ctx->nodeFrontier, neighbor))
        ctx->nodeCount++;
}

static u8 *ReconstructPath(struct PathNode *targetNode, u8 facingDirection)
{
    u32 moves = 0;
    for (struct PathNode *it = targetNode; it != NULL; it = it->parent)
    {
        if (it->parent != NULL)
            moves++;
    }

    // Plus begin, end and facing direction, if possible.
    u32 extraMoves = (facingDirection == DIR_NONE) ? 2 : 3;
    u8 *movementScript = Alloc(sizeof(u8) * (moves + extraMoves));

    movementScript[0] = MOVEMENT_ACTION_GENERATED_BEGIN; // marker

    u32 index = moves + 1; // +1 for the marker
    for (struct PathNode *it = targetNode; it != NULL; it = it->parent)
    {
        if (it->parent == NULL)
            break;

        movementScript[--index] = it->move;
    }

    index = moves + 1;
    if (facingDirection != DIR_NONE)
        movementScript[index++] = MOVEMENT_ACTION_FACE_DOWN + facingDirection - 1;

    movementScript[index] = MOVEMENT_ACTION_GENERATED_END;

    return movementScript;
}

static inline bool32 PathFinderTargetReached(struct PathFinderContext *ctx, struct PathNode *node)
{
    if (ctx->target.x == node->x && ctx->target.y == node->y)
        return TRUE;

    return FALSE;
}

static u8 CheckForPathFinderCollision(struct ObjectEvent *objectEvent, struct PathNode *node, s16 x, s16 y, u8 direction)
{
    u8 nextBehavior = MapGridGetMetatileBehaviorAt(x, y);
    u8 currentBehavior = MapGridGetMetatileBehaviorAt(node->x, node->y);

    if (GetLedgeJumpDirectionWithBehavior(direction, nextBehavior) != DIR_NONE)
        return COLLISION_LEDGE_JUMP;

    return GetCollisionWithBehaviorsAtCoords(objectEvent, x, y, node->elevation, direction, currentBehavior, nextBehavior);
}

static inline u32 ManhattanDistance(s16 x1, s16 y1, s16 x2, s16 y2)
{
    s16 dx = x2 - x1;
    s16 dy = y2 - y1;

    dx = (dx ^ (dx >> 15)) - (dx >> 15);
    dy = (dy ^ (dy >> 15)) - (dy >> 15);

    return (u32)(dx + dy);
}

//////////////////////////////////
// Nodes /////////////////////////
//////////////////////////////////

static inline struct PathNode *PathNode_Create(struct PathFinderContext *ctx, s16 x, s16 y, u32 costG, struct PathNode *parent)
{
    if (ctx->maxNodes == ctx->nodeCount)
        return NULL;

    struct PathNode *node = &ctx->nodeBuffer[ctx->nodeCount];
    u32 costH = PATH_FINDER_WEIGHT * ManhattanDistance(x, y, ctx->target.x, ctx->target.y);

    node->x = x;
    node->y = y;
    node->elevation = PathNode_GetElevation(parent, x, y);
    node->costG = costG;
    node->costF = costG + costH;
    node->parent = parent;

    return node;
}

static inline u8 PathNode_GetElevation(struct PathNode *parent, s16 x, s16 y)
{
    u8 elevation = MapGridGetElevationAt(x, y);
    if (elevation == PATH_FINDER_MAX_ELEVATION)
    {
        if (parent == NULL)
            return elevation;

        elevation = parent->elevation;
    }

    return elevation;
}

static inline bool32 PathNode_HasLowerCost(struct PathNode *node1, struct PathNode *node2)
{
    return (node1->costF) < (node2->costF);
}

static inline bool32 PathNode_Equal(struct PathNode *node1, struct PathNode *node2)
{
    if (node1->x == node2->x &&
        node1->y == node2->y &&
        node1->elevation == node2->elevation)
    {
        return TRUE;
    }

    return FALSE;
}

static inline u32 PathNode_Hash(struct PathNode *node)
{
    u32 x = (u32)((u16)node->x);
    u32 y = (u32)((u16)node->y);
    u32 elevation = (u32)node->elevation;

    // spatial hash
    u32 hash = (x * 73856093u) ^ (y * 19349663u) ^ (elevation * 83492791u);

    // fmix32
    hash ^= (hash >> 16);
    hash *= 0x85ebca6bu;
    hash ^= (hash >> 13);

    return hash;
}

//////////////////////////////////
// Priority Queue ////////////////
//////////////////////////////////

static inline u32 GetLeftChild(u32 index)
{
    return 2 * index + 1;
}

static inline u32 GetParent(u32 index)
{
    return (index - 1) / 2;
}

static struct PathQueue PathQueue_Create(u32 capacity)
{
    struct PathQueue queue;

    queue.nodes = Alloc(sizeof(struct PathNode *) * capacity);
    queue.capacity = capacity;
    queue.size = 0;

    return queue;
}

static void PathQueue_Destroy(struct PathQueue *queue)
{
    Free(queue->nodes);
    queue->size = 0;
    queue->capacity = 0;
}

static bool32 PathQueue_Push(struct PathQueue *queue, struct PathNode *node)
{
    if (queue->size >= queue->capacity)
        return FALSE;

    u32 index = queue->size;
    queue->nodes[index] = node;
    queue->size++;

    PathQueue_HeapifyUp(queue, index);

    return TRUE;
}

static bool32 PathQueue_Pop(struct PathQueue *queue, struct PathNode **outNode)
{
    if (queue->size == 0)
        return FALSE;

    *outNode = queue->nodes[0];
    queue->size--;

    if (queue->size != 0)
    {
        queue->nodes[0] = queue->nodes[queue->size];
        PathQueue_HeapifyDown(queue, 0);
    }

    return TRUE;
}

static inline void PathQueue_HeapifyUp(struct PathQueue *queue, u32 index)
{
    struct PathNode **nodes = queue->nodes;
    struct PathNode *temp = nodes[index];

    while (index != 0)
    {
        u32 parent = GetParent(index);

        if (!PathNode_HasLowerCost(temp, nodes[parent]))
            break;

        nodes[index] = nodes[parent];
        index = parent;
    }

    nodes[index] = temp;
}

static inline void PathQueue_HeapifyDown(struct PathQueue *queue, u32 index)
{
    struct PathNode **nodes = queue->nodes;
    struct PathNode *temp = nodes[index];

    while (TRUE)
    {
        u32 left = GetLeftChild(index);
        if (left >= queue->size)
            break;

        u32 best = left;
        u32 right = left + 1;

        if (right < queue->size && PathNode_HasLowerCost(nodes[right], nodes[left]))
            best = right;

        if (!PathNode_HasLowerCost(nodes[best], temp))
            break;

        nodes[index] = nodes[best];
        index = best;
    }

    nodes[index] = temp;
}

//////////////////////////////////
// Set ///////////////////////////
//////////////////////////////////

static inline u32 NextPowerOfTwo(u32 num)
{
    if (num == 0)
        return 1;

    num--;
    num |= num >> 1;
    num |= num >> 2;
    num |= num >> 4;
    num |= num >> 8;
    num |= num >> 16;
    num++;

    return num;
}

static struct PathList PathList_Create(u32 capacity)
{
    struct PathList list;
    capacity = NextPowerOfTwo(capacity);

    list.nodes = AllocZeroed(sizeof(struct PathNode *) * capacity);
    list.capacity = capacity;
    list.mask = capacity - 1;
    list.size = 0;

    return list;
}

static void PathList_Destroy(struct PathList *list)
{
    Free(list->nodes);
    list->capacity = 0;
    list->size = 0;
}

static bool32 PathList_TryInset(struct PathList *list, struct PathNode *node, struct PathNode **out)
{
    u32 index = PathNode_Hash(node) & list->mask;

    for (u32 i = 0; i < list->capacity; i++)
    {
        struct PathNode *current = list->nodes[index];

        if (current == NULL)
        {
            list->nodes[index] = node;
            list->size++;
            *out = node;

            return TRUE;
        }
        else if (PathNode_Equal(current, node))
        {
            *out = current;
            return FALSE;
        }

        index = (index + 1) & list->mask;
    }

    return FALSE;
}

static bool32 PathList_HasNode(struct PathList *list, struct PathNode *node)
{
    u32 index = PathNode_Hash(node) & list->mask;

    for (u32 i = 0; i < list->capacity; i++)
    {
        struct PathNode *current = list->nodes[index];

        if (current == NULL)
            return FALSE;

        if (PathNode_Equal(current, node))
            return TRUE;

        index = (index + 1) & list->mask;
    }

    return FALSE;
}
