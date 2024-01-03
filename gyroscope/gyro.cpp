#include <librealsense2/rs.hpp>
#include <iostream>

int main() {
    // Initialize the RealSense pipeline
    rs2::pipeline pipe;

    // Start streaming with a configuration that includes gyro
    rs2::config cfg;
    cfg.enable_stream(RS2_STREAM_GYRO, RS2_FORMAT_MOTION_XYZ32F);

    // Start the pipeline with the given configuration
    rs2::pipeline_profile pipeline_profile = pipe.start(cfg);

    // Wait for the first frame to ensure the gyro sensor is initialized
    rs2::frameset frames = pipe.wait_for_frames();
    rs2::motion_frame gyro_frame = frames.first_or_default(RS2_STREAM_GYRO);

    if (!gyro_frame) {
        std::cerr << "Gyroscope sensor not found." << std::endl;
        return EXIT_FAILURE;
    }

    // Main loop to capture and print gyroscope data
    while (true) {
        frames = pipe.wait_for_frames();
        gyro_frame = frames.first_or_default(RS2_STREAM_GYRO);

        rs2_vector gyro_data = gyro_frame.as<rs2::motion_frame>().get_motion_data();
        std::cout << "Gyroscope Data - X: " << gyro_data.x << " Y: " << gyro_data.y << " Z: " << gyro_data.z << std::endl;

    }

    // Stop the pipeline
    pipe.stop();

    return EXIT_SUCCESS;
}
