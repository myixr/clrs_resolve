function LEFT( i ){
	return 2*i+1;
}

function RIGHT( i ){
	return 2*i+2;
}

function PARENT( i ){
	return Math.floor((i-1)/2)
}

function MAX_HEAPIFY( A, i ){
	var l = LEFT(i);
	var r = RIGHT(i);
	var largest = i;

	if( l<A.length && A[l]>A[largest] ){
		largest = l;
	}
	if( r<A.length && A[r]>A[largest] ){
		largest = r;
	}

	if( largest != i ){
		var tmp = A[i];
		A[i] = A[largest];
		A[largest] = tmp;
		MAX_HEAPIFY( A, largest );
	}
}

function BUILD_MAX_HEAP( A ){
	for( var i=Math.floor(A.length/2)-1; i>=0; --i ){
		MAX_HEAPIFY( A, i );
	}
}


function printHeap( A ){
	var line_cnt = 1;
	var idx = 0;
	while( idx < A.length ){
		console.log( A.slice(idx,idx+line_cnt) );
		idx = idx + line_cnt;
		line_cnt = line_cnt*2;
	}
}

var A = [ 5,3,17,10,84,19,6,22,9 ];
printHeap( A );
BUILD_MAX_HEAP(A);
printHeap( A );
