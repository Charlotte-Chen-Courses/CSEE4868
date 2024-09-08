#
# Env variables
#

OPENCV ?= /opt/opencv

#
# Compiler flags
#

CXX = g++

CXXFLAGS = -O3        \
           -Wall      \
           -Werror    \
           -std=c++11

#
# Linker flags
#

LDLIBS = -L$(OPENCV)/lib64

LDFLAGS = -lopencv_features2d \
          -lopencv_imgcodecs  \
          -lopencv_videostab  \
          -lopencv_stitching  \
          -lopencv_objdetect  \
          -lopencv_calib3d    \
          -lopencv_highgui    \
          -lopencv_imgproc    \
          -lopencv_photo      \
          -lopencv_video      \
          -lopencv_flann      \
          -lopencv_core       \
          -lopencv_ml

#
# Include flags
#

#
# Add -I$(OPENCV)/include to INCDIR and other directories
#  you may need to compile the Mojo application.
#
INCDIR = -I$(OPENCV)/include -I./inc

INCDEP := $(wildcard ./inc/*.h)

TARGET := dwarf

SRCFILE := $(wildcard ./src/*.cpp)
#
# Rules
#

all:	$(TARGET) 


#
# Model
#

./models/dwarf7.mojo:
		cp -f /opt/dwarf_model/dwarf7.mojo $@

data: ./models/dwarf7.mojo

#
# Target
#

dwarf: $(INCDEP)
	$(CXX) $(CXXFLAGS) $(INCDIR) $(SRCFILE) -o $@ $^ $(LDLIBS) $(LDFLAGS) 

#
# Run
#

dwarf-run-airplane: $(TARGET)
	@LD_LIBRARY_PATH=/opt/opencv/lib64:$$LD_LIBRARY_PATH ./$(TARGET) data/airplane.bmp

dwarf-run-frog: $(TARGET)
	@LD_LIBRARY_PATH=/opt/opencv/lib64:$$LD_LIBRARY_PATH ./$(TARGET) data/frog.bmp 

#
# Clean
#

clean:
	@rm -f $(TARGET) *.o

#
# .Phony
#

.PHONY: all clean dwarf-run-airplane dwarf-run-frog

