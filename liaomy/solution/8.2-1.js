function countingSort( A, B, k ){
	var count = [];
	for (var i = 0; i <= k; i++) { count[i] = 0; }
	for (var i = 0; i < A.length; i++) {
		count[A[i]] = count[A[i]]+1
	}

	for( var i=1; i<=k; ++i ){
		count[i] = count[i-1] + count[i];
	}

	for( var i=0; i<A.length; ++i ){
		B[count[A[i]]-1] = A[i];
		count[A[i]] --;
	}

}

var A = [ 3,6,0,2,0,1,3,4,6,1,3,2];
var B = [];

console.log( "A=", A );
countingSort( A,B, 6 );
console.log( "B=", B );
