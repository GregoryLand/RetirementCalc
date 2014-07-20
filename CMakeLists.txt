################################################################################################################
# CMake Required Build order
# http://wiki.ros.org/catkin/CMakeLists.txt
#Required CMake Version (cmake_minimum_required)
#Package Name (project())
#Find other CMake/Catkin packages needed for build (find_package())
#Message/Service/Action Generators (add_message_files(), add_service_files(), add_action_files())
#Invoke message/service/action generation (generate_messages())
#Specify package build info export (catkin_package())
#Libraries/Executables to build (add_library()/add_executable()/target_link_libraries())
#Tests to build (catkin_add_gtest())
#Install rules (install())
################################################################################################################

# 1) Basics
cmake_minimum_required( VERSION 3.0 )

# 2) Declare the Lorei_2.0 project 
project( RetirementCalc )

# Allow Cmake to build folders 
set_property( GLOBAL PROPERTY USE_FOLDERS ON )

# Compiler Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Setup the subproject RetirementCalcLib
# Setup the Header and Source Variables
file( GLOB RetirementCalc_LIB_HEADERS
        "RetirementCalcLib/Src/*.h" ) 
        
file( GLOB RetirementCalc_LIB_SOURCES 
        "RetirementCalcLib/Src/*.cpp"  ) 
        
# Create the Lib
add_library( RetirementCalcLib STATIC ${RetirementCalc_LIB_HEADERS} ${RetirementCalc_LIB_SOURCES} )
add_subdirectory( RetirementCalcLib )

# Setup subproject LoreiTest our boost unit test framework
add_subdirectory( RetirementCalcTest )
add_dependencies( RetirementCalcTest RetirementCalcLib )

# Setup our Qt based GUI
add_subdirectory( RetirementCalcGUI )
add_dependencies( RetirementCalcGUI RetirementCalcLib )
