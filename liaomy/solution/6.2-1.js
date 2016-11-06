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

function printHeap( A ){
	var line_cnt = 1;
	var idx = 0;
	while( idx < A.length ){
		console.log( A.slice(idx,idx+line_cnt) );
		idx = idx + line_cnt;
		line_cnt = line_cnt*2;
	}
}

var A = [ 27,17,3,16,13,10,1,5,7,12,4,8,9,0 ];
printHeap( A );
MAX_HEAPIFY( A, 2 );
printHeap( A );
