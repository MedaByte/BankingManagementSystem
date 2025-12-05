async function LoadAllAccountFromCpp(){
        const response = await fetch('https://nonextensively-monodomous-juana.ngrok-free.dev/submit',
          {
            method : 'POST',
            headers:{'Content-Type':'application/json'},
            body : JSON.stringify({ command: "LoadAllAccounts" })
          }
        );
        let data = await response.json();
        return data ;

}