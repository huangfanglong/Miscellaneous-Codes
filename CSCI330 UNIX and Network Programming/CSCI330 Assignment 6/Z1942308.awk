BEGIN  {
		print "\tWord\tCount"
		print "----------------------"
		count = 0
		}
		
$0 !~ /#/{

		for(i=1;i<=NF;i++) { 
			c[$i]++
			count++
			}
}

END	{
	for(words in c) {
	if (length(words) > 3 && c[words] > 2) {
		printf("%12s%5d\n", words, c[words])
		}
		}
	print "----------------------"
	printf("Number of words:  " count)
	printf("\n")
	}
