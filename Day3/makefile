#CFLAGS  = -O2 -g3 -Wall -std=c++0x
#LDFLAGS = -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab -lpthread -lrt -lm -lstdc++
#LDFLAGS += `pkg-config --cflags --libs opencv`
#INC     = -I/usr/local/include/opencv -I../../Monitor/include  $(XML_FLAGS)
#LIB     = -L/usr/local/lib -L../../Monitor/lib $(XML_LIBS)

#INCSRC  =
#all: test

#test: test.o
#	$(CXX) test.o $(INC) $(CFLAGS) $(LIB) $(LDFLAGS) -o $@



all:task1

task1: histogr.o
	g++ -o task1 -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_highgui -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_videoio -lopencv_videostab -lpthread -lrt -lm -lstdc++ histogr.o -L/usr/local/lib 
 

histogr.o: histogr.cpp
	g++ -c  histogr.cpp -I/opt/opencv/include/opencv

clean:
	rm *.o
