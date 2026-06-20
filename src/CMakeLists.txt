# Include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Create executable from main.cpp
add_executable(BankingSystem main.cpp)

# Link libraries (add more if needed)
target_include_directories(BankingSystem PRIVATE ${CMAKE_SOURCE_DIR}/include)