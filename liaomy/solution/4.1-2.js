function maxSubArray( input_array ){
	result = {}
	for( var i=0; i<input_array.length; ++i ){
		var sum = 0;
		for( var j=i; j<input_array.length; ++j ){
			sum += input_array[j];
			if( result.sum==null || sum > result.sum ){
				result.sum = sum;
				result.begin = i;
				result.end = j;
			}
		}
	}
	return result;
}

var input_array = [13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7 ];
console.log( "input:", input_array );
console.log( "result:", maxSubArray(input_array));