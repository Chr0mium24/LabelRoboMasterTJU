# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

LabelRoboMasterTJU is a Qt-based C++ application for labeling RoboMaster competition images. It's specialized for TJURM (Tianjin University RoboMaster) team's data annotation needs, featuring AI-assisted automatic labeling and image brightness adjustment capabilities.

## Build System and Commands

### Build Dependencies
- Qt 5.12.10+ or 5.15.2+ (Core, Gui, Widgets, Svg modules)
- OpenCV 4.5.3+
- CMake 3.12+
- C++17 compiler

### Build Commands
```bash
# Create build directory and compile
mkdir build
cd build
cmake ..
make

# For release builds with packaging
make install DESTDIR=AppDir
```

### Platform-Specific Builds

#### Ubuntu/Linux
- Uses GitHub Actions workflow (`.github/workflows/ubuntu.yml`)
- Requires Intel OpenVINO 2021.4.689 for AI inference
- Creates AppImage packages using linuxdeploy

#### Windows
- Uses GitHub Actions workflow (`.github/workflows/windows.yml`)
- Supports both OpenCV and OpenVINO backends
- Uses NMake for building with MSVC
- Package script: `scripts/windows-publish.ps1`

## Architecture

### Core Components

1. **MainWindow** (`mainwindow.h/cpp`)
   - Main application window and UI controller
   - Manages file navigation, brightness controls, and labeling operations
   - Handles smart labeling triggers and interpolation

2. **DrawOnPic** (`drawonpic.h/cpp`)
   - Custom QLabel widget for image display and annotation
   - Handles mouse interactions for drawing bounding boxes
   - Manages coordinate transformations between image and display spaces
   - Implements zoom, pan, and label visualization

3. **SmartModel** (`model.hpp/cpp`)
   - AI inference engine using OpenCV DNN or OpenVINO
   - Provides automatic object detection for RoboMaster targets
   - Supports brightness adjustment parameters (alpha, beta)

4. **LabelDialog** (`labeldialog.h/cpp`)
   - Dialog for editing label properties and categories

### Label Categories

The system recognizes 12 RoboMaster object types:
- Sentry (0), Robot numbers 1-5 (1-5), Outpost (6)
- Base_small (7), Base_big (8), 3_big (9), 4_big (10), 5_big (11)

### Key Features

1. **AI-Assisted Labeling**
   - Automatic object detection via `SmartModel::run()`
   - Smart labeling for single images or batch processing
   - Configurable confidence thresholds

2. **Image Brightness Adjustment**
   - Linear transformation: `y = alpha * x + beta`
   - UI controls for real-time brightness/contrast adjustment
   - Helps with difficult-to-see dark images

3. **Interactive Annotation**
   - Mouse-based bounding box drawing and editing
   - Keyboard shortcuts for efficiency
   - Focus-based box selection and modification

4. **File Management**
   - Directory-based image browsing
   - Automatic label file saving (alongside images)
   - Navigation slider and prev/next buttons

## Development Notes

### Coordinate Systems
- Uses Qt's QTransform for coordinate transformations
- `norm2img`: normalized coordinates to image coordinates
- `img2label`: image coordinates to display coordinates
- All labels stored in normalized coordinates

### UI Framework
- Built with Qt Designer (.ui files)
- Uses Qt's signal-slot mechanism for component communication
- Custom drawing with QPainter for overlays

### Resource Management
- SVG icons stored in Qt resource system (`resource.qrc`)
- Standard tag renderers for different object types
- Icon files in `resource/` directory