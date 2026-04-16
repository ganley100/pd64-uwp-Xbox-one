cmake_minimum_required(VERSION 3.14)
include(FetchContent)

# Setup UWP platform
set(CMAKE_SYSTEM_NAME WindowsStore)
set(CMAKE_SYSTEM_VERSION 10.0.19041.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch shared UWP deps
FetchContent_Declare(UwpLibs
    GIT_REPOSITORY https://github.com/worleydl/uwp-dep.git
    GIT_TAG 3960693ee292522a5bcb58bc7d4136a0bb8864af 
)
FetchContent_MakeAvailable(UwpLibs)

# Define project
project(pd64-uwp LANGUAGES CXX)
set_directory_properties(PROPERTIES VS_STARTUP_PROJECT ${PROJECT_NAME})

# Config for main aquaria build
set(PD_DIR CACHE PATH "")

add_executable(${PROJECT_NAME} WIN32
	main.cpp
)

set(BinDeps
	${CMAKE_CURRENT_BINARY_DIR}/_deps/uwplibs-src/x64/bin/dxil.dll
	${CMAKE_CURRENT_BINARY_DIR}/_deps/uwplibs-src/x64/bin/libgallium_wgl.dll
	${CMAKE_CURRENT_BINARY_DIR}/_deps/uwplibs-src/x64/bin/libuwp.dll
	${CMAKE_CURRENT_BINARY_DIR}/_deps/uwplibs-src/x64/bin/opengl32.dll
	${CMAKE_CURRENT_BINARY_DIR}/_deps/uwplibs-src/x64/bin/SDL2.dll
	${CMAKE_CURRENT_BINARY_DIR}/_deps/uwplibs-src/x64/bin/zlib1.dll
	${CMAKE_CURRENT_BINARY_DIR}/_deps/uwplibs-src/x64/bin/z-1.dll

	${PD_DIR}/libpd.x86_64.dll

	Package.appxmanifest
)
source_group("BinDeps" FILES ${BinDeps})
set_source_files_properties(${BinDeps} PROPERTIES
	VS_COPY_TO_OUT_DIR Always
	VS_DEPLOYMENT_CONTENT TRUE
	VS_DEPLOYMENT_LOCATION "."
)

set(PkgAssets
	Assets/LockScreenLogo.scale-200.png
	Assets/Square44x44Logo.targetsize-24_altform-unplated.png
	Assets/Square44x44Logo.scale-200.png
	Assets/Square150x150Logo.scale-200.png
	Assets/StoreLogo.png
)
source_group("PkgAssets" FILES ${PkgAssets})
set_source_files_properties(${PkgAssets} PROPERTIES
	#VS_COPY_TO_OUT_DIR Always
	VS_DEPLOYMENT_CONTENT TRUE
	VS_DEPLOYMENT_LOCATION "Assets"
)

# Setup data deployment
file(GLOB_RECURSE DATA_FILES
	RELATIVE ${CMAKE_SOURCE_DIR}/..
	${CMAKE_SOURCE_DIR}/../assets/*
)

foreach(ASSET ${DATA_FILES})
	set(FULL_PATH "${CMAKE_SOURCE_DIR}/../${ASSET}")

	get_filename_component(DEST_DIR ${ASSET} DIRECTORY)

	set_source_files_properties("${FULL_PATH}" PROPERTIES
		VS_COPY_TO_OUT_DIR Always
		VS_DEPLOYMENT_CONTENT TRUE
		VS_DEPLOYMENT_LOCATION "${DEST_DIR}" # preserves folder structure
	)

	target_sources(${PROJECT_NAME} PRIVATE "${FULL_PATH}")
	source_group("BinData" FILES "${FULL_PATH}")
endforeach()

target_sources(${PROJECT_NAME} PRIVATE
	${BinDeps}
	${PkgAssets}
)

set(BinLibs
	uwp::LIBUWP
	uwp::SDL2

	${PD_DIR}/libpd.x86_64.dll.a

	WindowsApp.lib
	OneCore.lib
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${BinLibs})
