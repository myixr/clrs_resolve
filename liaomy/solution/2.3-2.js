function MERGE( A, p, q, r ){
	var n1 = q-p+1;
	var n2 = r-q;

	var L = [];
	var R = [];
	for( var i=0; i<n1; ++i ){
		L.push( A[i+p] );
	}
	for( var i=0; i<n2; ++i ){
		R.push( A[i+1+q] );
	}

	var idxL = 0;
	var idxR = 0;
	while( idxL<n1 && idxR<n2 ){
		if( L[idxL] <= R[idxR] ){
			A[idxL+idxR+p] = L[idxL];
			idxL ++;
		}
		else{
			A[idxL+idxR+p] = R[idxR];
			idxR ++;
		}
	}

	while( idxL < n1 ){
		A[idxL+idxR+p] = L[idxL];
		idxL ++;
	}
	while( idxR < n2 ){
		A[idxL+idxR+p] = R[idxR];
		idxR ++;
	}
}

function MERGE_SORT( A, p, r ){
	if( p < r ){
		var q = Math.floor( (p+r)/2 );
		MERGE_SORT( A, p, q );
		MERGE_SORT( A, q+1, r );
		MERGE( A, p, q, r );
	}
	return A;
}

var N = 10;
var arr = [];
for( var i=0; i<N; ++i ){
	arr.push( Math.floor( Math.random()*1000 ) );
}

console.log( 'input :', arr.join(',') );
console.log( 'output:', MERGE_SORT(arr, 0, arr.length-1).join(',') );

