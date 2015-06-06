CXX = g++

CXXFLAGS =	-O2 -g -Wall

SRCS = SpecModel.cpp HIModel.cpp GAModel.cpp CGFModel.cpp SegmentData.cpp Utils.cpp Parameter.cpp AdmixInfer.cpp

OBJS = $(SRCS:.cpp=.o)

INCLUDES = 

LIBS = 

TARGET = AdmixInfer

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) 

all:	$(TARGET)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
