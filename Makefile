make:
	g++  -o cluster -std=c++11 -g3 prj2.cpp utils.cpp Cluster.cpp Initialisation.cpp Assignment.cpp Cosine_G.cpp Cosine_Hash_Function.cpp Cosine_Hashtable.cpp Cosine_Lsh_Hashtable.cpp G.cpp Hash_Function.cpp Hashtable.cpp Lsh_Hashtable.cpp Search.cpp Update.cpp Evaluation.cpp

clean:
	rm cluster
