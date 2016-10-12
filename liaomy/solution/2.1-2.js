function INSERTION_SORT( arr ){
	var i,j;
	for( j=1; j<arr.length; j++ ){
		var key = arr[j];
		i = j-1;
		while( i>=0 && key>arr[i] ){
			arr[i+1] = arr[i];
			i--;
		}
		arr[i+1] = key;
	}
	return arr;
}

data = [ 3,2,1,4,6,3,8,2 ]
console.log( data );
console.log( INSERTION_SORT(data) );
