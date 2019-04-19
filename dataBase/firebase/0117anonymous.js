// JavaScript Document
(function(){ //立即匿名
	var config = {
		apiKey: "AIzaSyBBpKMDQk2He3D3uPVrypr0namRTJes2pk",
		authDomain: "first20190109.firebaseapp.com",
		databaseURL: "https://first20190109.firebaseio.com",
		projectId: "first20190109",
		storageBucket: "first20190109.appspot.com",
		messagingSenderId: "1026634990833"
	  };
	  firebase.initializeApp(config);
  
	const aLogin=document.getElementById('aLogin');
	const aLogout=document.getElementById('aLogout');
	const aaFrame=document.getElementById('aaFrame');
	const auth=firebase.auth();
  
	aLogin.addEventListener();

	aLogin.addEventListener();

	aaFrame.auth().onAuthStateChanged();


	dbRefproduct.once('value',snap=>{snap.forEach(function(childSnap){				  		
										var childKey=childSnap.key;
										var childVal=childSnap.val();
										
										console.log(childKey);
										console.log(childVal);

										var r=tblProduct.insertRow(trIndex);

										var childID=r.insertCell(0);
										var childName=r.insertCell(1);
										var childPrice=r.insertCell(2);
									
										childID.appendChild(document.createTextNode(childKey));
										childName.appendChild(document.createTextNode(childVal.name));
										childPrice.appendChild(document.createTextNode(childVal.price));
										trIndex=trIndex+1;
									});//子項(迴圈項)
					  			document.getElementById('pCount').innerHTML="目前共有 " + (trIndex-1) + "筆資料<br>";
							});//父項

}());