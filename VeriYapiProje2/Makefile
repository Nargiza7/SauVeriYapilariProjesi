all:derle bagla calistir
derle:
	g++ -c -I "./include" ./src/main.cpp -o ./lib/main.o
	g++ -c -I "./include" ./src/Node.cpp -o ./lib/Node.o
	g++ -c -I "./include" ./src/BinaryTree.cpp -o ./lib/BinaryTree.o
	g++ -c -I "./include" ./src/LinkedList.cpp -o ./lib/LinkedList.o
	g++ -c -I "./include" ./src/TreeNode.cpp -o ./lib/TreeNode.o
	g++ -c -I "./include" ./src/FileReader.cpp -o ./lib/FileReader.o
bagla:
	g++ ./lib/BinaryTree.o ./lib/LinkedList.o ./lib/FileReader.o ./lib/Node.o ./lib/TreeNode.o ./lib/main.o -o ./bin/program
calistir:
	./bin/program