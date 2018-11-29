make:
	g++  -o cluster -std=c++11 -g3 prj2.cpp utils.cpp Cluster.cpp Initialisation.cpp

clean:
	rm cluster
