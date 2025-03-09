const pokemonObjList = {};
function fetchPokemonListAndAddToSideBar() {
    pokeAPIGet("pokemon","limit=100&offset=0")
    .then(data => {
        const pokemonList = data.results;
        // Loop through each Pokémon and create a sidebar item.
        pokemonList.forEach((pokemon, index) => {
            // Create a new div for each Pokémon.
            const item = document.createElement('div');
            item.classList.add('pokemon-item');
            // Use a predictable sprite URL; index+1 corresponds to the Pokémon's ID.
            item.innerHTML = `<img src="https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/${index+1}.png" alt="${pokemon.name}">
                                <span>${pokemon.name}</span>`;

            console.log(item);

            // -------------------------------------
            // TO DO: Append the item to the sidebar.
            // -------------------------------------
            document.getElementById("sidebar").appendChild(item);
            // -------------------------------------
            // TO DO: Complete the click event listener to each item.
            // -------------------------------------
            item.addEventListener('click', () => {
                if (pokemonObjList[pokemon.name]) {
                    // Render the Pokémon's data card.
                    document.getElementById('card-display-area').innerHTML = pokemonObjList[pokemon.name].renderInfoTable();
                    return;
                }else{
                    pokeAPIGet(`pokemon/${index+1}`)
                    .then(data => {
                        // TO DO: Create a new Pokémon object.
    
                        const pokemonObj = new PokemonData(data);
                        // TO DO: Store the Pokémon object in the pokemonObjList.
                        pokemonObjList[pokemon.name] = pokemonObj;
                        // Render the Pokémon's data card.
                        document.getElementById('card-display-area').innerHTML = pokemonObj.renderInfoTable();
                    })
                    .catch(error => console.error("Error fetching Pokémon:", error));
                }
            });
        });
    });
}
