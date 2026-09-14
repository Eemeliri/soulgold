The build generates `src/data/docs_qr.h` from `include/config/version.h`.
Both documentation links include `?version=<DISPLAY_VERSION>`. Changing the
version automatically regenerates the matrices before dependency scanning.
Run `python3 tools/docs_qr/generate.py` to regenerate them manually.

In game, open the pause menu and select Docs below Option. A or Left/Right
switches between Documentation and Guides. B returns to the open pause menu.
The QR screen works on hardware and emulators without companion software.

Generation needs Python 3 and no installed packages or internet connection.
`qrcodegen.py` is the unmodified Python library from Project Nayuki's
[QR Code generator v1.8.0](https://github.com/nayuki/QR-Code-generator/tree/v1.8.0/python).
Its MIT license is included at the top of that file.

The ROM draws version-4 QR codes (33 x 33 modules), with medium error correction,
at three screen pixels per module and a four-module white border. The resulting
123 x 123 image fits the GBA display. A version string that makes either URL
too long fails generation instead of producing an oversized or truncated code.
