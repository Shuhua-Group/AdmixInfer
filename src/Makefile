CXX = g++

CXXFLAGS =	-O2 -Wall -fopenmp

SRCS = SpecModel.cpp HIModel.cpp GAModel.cpp CGFModel.cpp SegmentData.cpp Utils.cpp Parameter.cpp AdmixInfer.cpp

OBJS = $(SRCS:.cpp=.o)

INCLUDES = 

LIBS = 

TARGET = AdmixInfer

$(TARGET):	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS) 

all:	$(TARGET)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
