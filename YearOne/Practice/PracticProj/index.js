
const scrollContainer = document.querySelector('.flex-container');

scrollContainer.addEventListener('wheel', (event) => {
    event.preventDefault();
    scrollContainer.scrollLeft += event.deltaY * 16.94;

});

function ScrollRight(){
    scrollContainer.scrollLeft += 2000;
}

function ScrollLeft(){
    scrollContainer.scrollLeft -= 2000;
}



document.addEventListener("DOMContentLoaded", function() {
    let favouriteButtons = document.getElementsByClassName("favouriteButton");

    Array.from(favouriteButtons).forEach(function(favouriteButton) {
        favouriteButton.addEventListener("click", function() {
            if (favouriteButton.src.endsWith("images/FavouriteFilled.png")) {
                favouriteButton.src = "images/Favourite.png";
            } else {
                favouriteButton.src = "images/FavouriteFilled.png";
            }
        });
    });
});

arrowsContainer = document.getElementById("arrowsDiv")
arrowsContainer.children[1].addEventListener('click', (event) => {
    ScrollRight();
    console.log("Sdasdad")
})

arrowsContainer.children[0].addEventListener('click', (event) => {
    ScrollLeft();
    console.log("Sdasdad")
})


/*heats = document.getElementById("Heats");
heats.addEventListener('click', (event) =>{
    const id = event.target
}*/

/*

table.addEventListener('click', (event) => {
    const id = event.target.closest("tr").id;
    console.log(id);

    ShowTransactionData(transactions.find((transaction) => transaction.id == id));
});
*/



