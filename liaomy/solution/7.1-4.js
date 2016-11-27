function exchange( A, p, q ){
	var tmp = A[p];
	A[p] = A[q];
	A[q] = tmp;
}

function PARTITION( A, p, r ){
	console.log( "P", A.slice(p,r+1) );
	var key = A[r];
	var i = p;
	var j = p;

	while( j<r ){
		if( A[j] < key ){
			if( i!=j){
				var tmp = A[i];
				A[i] = A[j];
				A[j] = tmp;
			}
			i++;
		}
		j++;
	}
	if( A[i] > key ){
		exchange( A,i,r ); 
	}
	console.log( "R", A.slice(p,r+1) );
	return i;
}

function QUICKSORT( A, p, r ){
	if( p<r ){
		q = PARTITION( A, p, r );
		QUICKSORT( A, p, q-1 );
		QUICKSORT( A, q+1, r );
	}
}

var A = [ 13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11 ];
QUICKSORT( A, 0, A.length-1 );
console.log( A );

