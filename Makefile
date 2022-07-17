src=./src
test=./test
pb=./pb
all:
	mkdir output
	mkdir output/include
	mkdir output/lib
	cd ${pb} && make
	cd ${src} && make
	cp -r output test/trpc
	cd ${test} && make
clean:
	rm -rf output
	cd ${pb} && make clean
	cd ${src} && make clean
	cd ${test} && make clean
