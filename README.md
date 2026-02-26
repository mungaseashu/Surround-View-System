Surround View System

A C++ based 360° Surround View System built using OpenCV that combines four camera inputs (front, back, left, right) into a single bird’s-eye view image.  

This project demonstrates real-time image processing, perspective transformation, and multi-image stitching similar to automotive parking assist systems.


Overview

The Surround View System:

- Captures images from four cameras
- Applies distortion correction
- Converts images into single image view
- Stitches all views into a seamless 360° composite image

It simulates the working of modern ADAS (Advanced Driver Assistance Systems) used in vehicles.


Features

- Multi-camera image processing  
- Perspective transformation (Bird’s Eye View)  
- Image stitching & blending  
- Real-time processing pipeline  
- Modular and extendable architecture  
- Implemented fully in C++ using OpenCV  


🛠️ Tech Stack

- C++
- OpenCV
- CMake
- Streamlit (for UI)


Installation & Setup

1️⃣ Clone the Repository

git clone https://github.com/mungaseashu/Surround-View-System.git
cd Surround-View-System

2️⃣ Create Build Directory

mkdir build
cd build

3️⃣ Generate Build Files

cmake ..

4️⃣ Build the Project

cmake --build .

▶️ Usage

Run the executable after building:
./SurroundViewSystem

📁 Project Structure

Surround-View-System/
│
├── src/                # Source files
├── images/             # Sample input images
├── output/             # Generated stitched output
├── CMakeLists.txt      # Build configuration
└── README.md


Working Pipeline
1️⃣ Image Acquisition
Four images are captured from different camera angles.

2️⃣ Distortion Correction
Removes lens distortion using calibration parameters.

3️⃣ Image Stitching
All transformed images are stitched together to generate a seamless surround view.


Sample Output

The system produces:
- Undistorted camera images
- Bird’s-eye transformed images
- Final stitched 360° surround view


Applications

- Autonomous driving research
- Parking assistance systems
- Advanced Driver Assistance Systems (ADAS)
- Robotics and surveillance systems
- Computer vision research


Future Improvements

- Real-time video stream integration
- GPU acceleration
- Seamless blending enhancement
- Deep learning based object detection integration
- ROS integration for robotics
