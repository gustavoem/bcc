$, = " ";
# for ($i = 0; $i < 10; $i++) { 
# 	@ar[$i] = $i;
# }
# print @ar;

#the oneline cat
#print while (<>);

#outro
next unless /^>/; 
s/(\d+) mais (\d+)/ $1 + $2/g;