for i in datasets/*.txt
do
	echo $i
	./main $i a > $i.result
	du -sh merged > $i.result.size
done
