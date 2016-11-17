function sort( A, idx ){
	var i,j;
	for( j=1; j<A.length; j++ ){
		var key = A[j];
		i = j-1;
		while( i>=0 && key[idx]<A[i][idx] ){
			A[i+1] = A[i];
			i--;
		}
		A[i+1] = key;
	}
	return A;
}

function radixSort( A, d ){
	sort( A, 2 );
	sort( A, 1 );
	sort( A, 0 );
}

var A = [ 3,6,0,2,0,1,3,4,6,1,3,2];
var B = [];

var words = [ "COW", "DOG", "SEA", "EUG", "ROW", "MOW", "BOX", "TAB", "BAR", "EAR", "TAR", "DIG", "BIG", "TEA", "NOW", "FOX" ]

var input = [];
for( var i=0; i<words.length; ++i ){
	input.push( words[i].split("") );
}

radixSort( input );
console.log( input );

