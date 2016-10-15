const crypto = require( 'crypto' );

function BIN_ADD( arr1, arr2 ){
	var c = 0;
	if( arr1.length != arr2.length ){
		return null;
	}
	var len = arr1.length;
	var result = [];
	for( var i=len-1; i>=0; --i ){
		c = arr1[i]+arr2[i]+c;
		result.push( c%2 );
		c = Math.floor(c/2);
	}
	if( c > 0 ){
		result.push( c );
	}
	return result.reverse();
}

arr1 = [];
arr2 = [];

for( var i=0; i<10; ++i ){
	arr1.push( crypto.randomBytes(1)[0]%2 );
	arr2.push( crypto.randomBytes(1)[0]%2 );
}

console.log( '  ', arr1 );
console.log( '+ ', arr2 );
console.log( '-------------------------------------');
var result = BIN_ADD( arr1, arr2 );
if( result.length == arr1.length ){
	console.log( '  ', BIN_ADD(arr1,arr2) );
}
else{
	console.log( BIN_ADD(arr1,arr2) );
}

