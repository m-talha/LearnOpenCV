set(PROJECT_NAME CameraCalibration)
project(${PROJECT_NAME} VERSION 1.0.0)

add_executable(${PROJECT_NAME} src/camera_calibration.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

install(TARGETS ${PROJECT_NAME} 
        RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/bin)