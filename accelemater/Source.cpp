#include <librealsense2/rs.hpp>
#include <iostream>

int main() {
    rs2::pipeline pipe;
    rs2::config cfg;

    // Enable Accelerometer
    cfg.enable_stream(RS2_STREAM_ACCEL, RS2_FORMAT_MOTION_XYZ32F);

    // Starting the RealSense Pipeline
    pipe.start(cfg);

    try {
        while (true) {
            // Wait for frame
            rs2::frameset frames = pipe.wait_for_frames();

            // to get accelermeter data
            rs2::motion_frame accel_frame = frames.first_or_default(RS2_STREAM_ACCEL);
            if (accel_frame) {
                rs2_vector accel_data = accel_frame.get_motion_data();
                std::cout << "Acceleration: X=" << accel_data.x << ", Y=" << accel_data.y << ", Z=" << accel_data.z << std::endl;
            }
        }
    }
    catch (const rs2::error& e) {
        std::cerr << "RealSense error: " << e.what() << std::endl;
    }

    return 0;
}
