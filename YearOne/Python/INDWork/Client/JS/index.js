function LogIn()
{
    fetch('http://127.0.0.1:5000/search', {
        method: 'POST',
        headers: {
            'Content-Type': 'text/plain'
        },
        body: JSON.stringify({login: 'Rengeka', password: '12345'})
    }).then(response => {
        if (response.ok) {
            console.log("Success");
        } else {
            console.log("Failed to send request. Status code:", response.status);
        }
    }).catch(error => {
        console.error("Error:", error);
    });
}

function SignIn()
{

}

function AddToFriends()
{

}

function SenMessage()
{

}

LogIn();