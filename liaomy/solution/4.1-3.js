function findMaxCrossingSubArray( input_array, low, mid, high ){
	var sum = 0;
	var left_sum = null;
	var left_idx = -1;
	var right_sum = null;
	var right_idx = -1;
	for( var i=mid; i>=low; --i ){
		sum += input_array[i];
		if( left_sum==null || left_sum<sum ){
			left_sum = sum;
			left_idx = i;
		}
	}
	sum = 0;
	for( var i=mid+1; i<=high; ++i ){
		sum += input_array[i];
		if( right_sum==null || right_sum<sum ){
			right_sum = sum;
			right_idx = i;
		}
	}
	result = {}
	result.sum   = right_sum + left_sum;
	result.begin = left_idx;
	result.end   = right_idx;
	return result;
}

function findMaxSubArray( input_array, low, high ){
	//console.log( low,high );
	if( high == low ){
		result = {};
		result.sum   = input_array[low];
		result.begin = low;
		result.end   = low;
		return result;
	}
	else{
		var mid = Math.floor( (low+high)/2 );
		var left_result  = findMaxSubArray( input_array, low,mid );
		var right_result = findMaxSubArray( input_array, mid+1, high );
		var cross_result = findMaxCrossingSubArray( input_array, low, mid, high );

		if( left_result.sum>cross_result.sum && left_result.sum>right_result.sum ){
			result = left_result;
		}
		else if( cross_result.sum>left_result.sum && cross_result.sum>right_result.sum ){
			result = cross_result;
		}
		else{
			result = right_result;
		}

		return result;
	}
}

var input_array = [13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7 ];
console.log( "input:", input_array );
console.log( "result:", findMaxSubArray(input_array,0,input_array.length-1));