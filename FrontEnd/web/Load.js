async function Load(CMD,info="10"){
        const response = await fetch('https://nonextensively-monodomous-juana.ngrok-free.dev/submit',
          {
            method : 'POST',
            headers:{'Content-Type':'application/json'},
            body : JSON.stringify({ command: CMD  , info : info})
          }
        );
        let data = await response.json();
        return data ;

}
function IND(arr,att,val){
  for(let i = 0 ; i < arr.length ; i++){
    if(arr[i][att]==val){
      return i ;
    }
  }
  return -1;
}