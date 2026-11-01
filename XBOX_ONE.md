# Perfect Dark UWP – Original Xbox One Guide

Target: **original Xbox One** (not Series), aiming for playable **60 FPS**.

> The existing public UWP builds were mainly validated on Series X|S. Original Xbox One is much weaker. Expect to use lower resolution and reduced effects.

## Requirements

- Xbox One (original / S / X) in **Developer Mode**
- NTSC final ROM (`pd.ntsc-final.z64`, md5 `e03b088b6ac9e0080440efed07c1e40f`)
- UWP package built from this repo (or an existing pd64-uwp package)

## Deploy

1. Open Xbox Device Portal in a browser (`https://<xbox-ip>:11443`).
2. **Apps → Install** and sideload the package.
3. Launch the app once so it creates LocalState folders.
4. In Device Portal, set the app type to **Game** (not App).  
   This unlocks expanded resources and is required for usable performance on original Xbox One.
5. Copy your ROM into:

   `LocalAppData/Perfect Dark/LocalState/` (or the path shown after first launch)

   Name it exactly:

   `pd.ntsc-final.z64`

6. Copy the sample config:

   `uwp/pd.ini.xboxone` → LocalState as `pd.ini`

## Recommended settings (original Xbox One / 60 FPS)

Start with the values in `uwp/pd.ini.xboxone`:

- 1280×720, fullscreen, exclusive
- VSync on, FramerateLimit 60
- MSAA 1, FramebufferEffects off, low anisotropic filtering
- MemorySize 16

If performance is still poor:

- Drop to 960×540 or 640×480
- Keep FramebufferEffects = 0
- Keep MSAA = 1

## Building the UWP package (Windows)

You need Visual Studio with UWP / Windows 10 SDK workload.

1. Build the game DLL with UWP compatibility:

   ```bat
   cmake -G "Unix Makefiles" -Bbuild -DUWP_COMPAT=ON .
   cmake --build build -j
   ```

   (Or equivalent MSYS2 / MinGW flow used by the main port.)

2. Point the UWP CMake project at the built DLL:

   ```bat
   cd uwp
   cmake -G "Visual Studio 17 2022" -A x64 -Bbuild -DPD_DIR=../build
   cmake --build build --config Release
   ```

3. Deploy the resulting package to the console via Device Portal or Visual Studio remote debugging.

## Known limitations

- OpenGL-on-UWP (Mesa/Gallium) stack is heavier on original Xbox One than on Series.
- Solid locked 60 FPS may require 720p or lower and reduced effects.
- External storage support is limited; internal LocalState is the reliable path.

## Feedback

If the game boots, report FPS, resolution used, and any crashes. That data is needed to tighten defaults further.
