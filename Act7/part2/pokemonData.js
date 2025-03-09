class PokemonData {
    constructor(data) {
        // Store the Pokémon's ID.
        this.id = data.id;

        // Store the Pokémon's name.
        this.name = data.name;
        
        // Store the Pokémon's types as an array of type names.
        this.types = data.types.map(typeInfo => typeInfo.type.name);

        this.image = data.sprites.front_default;

        // Store the full API data for the Pokémon.
        this.apiData = data;
    }
    toString() {
        if(this.name==undefined){
            return "Not properly initialized";
        }
        return `${this.id} : ${this.name} (${this.types.join(", ")})`;
    }

    // a getter method to return apiData
    getApiData(rendered = false){
        if(rendered){
            return JSON.stringify(this.apiData, null, 2);
        }else{
            return this.apiData;
        }
    }

    renderInfoTable(){
        return `
        <table class="pokemon-info-table">
            <thead>
                <tr><th>Attributes</th><th>Values</th></tr>
            </thead>
            <tbody>
                <tr>
                    <td>ID</td>
                    <td>${this.id}</td>
                </tr>
                <tr>
                    <td>Name</td>
                    <td>${this.name}</td>
                </tr>
                <tr>
                    <td>Types</td>
                    <td>${this.types.join(", ")}</td>
                </tr>
                <tr>
                    <td>Image</td>
                    <td>
                        <img class="pokemon-image" src="${this.image}" alt="Default image of ${this.name}"/>
                    </td>
                </tr>
                <tr>
                    <td>API Data</td>
                    <td><pre class="api-data">${this.getApiData(true)}</pre></td>
            </tbody>
        </table>
        `;
    }

}

function testPokemonDataClass(){
    // This function is here to help you observe how the PokemonData class works.
    // You can call this function from your browser's console to test the class.
    // Create a mock data object for a Pokémon.
    let mockData = {
        id: 1,
        name: "bulbasaur",
        types: [{type: {name: "grass"}}, {type: {name: "poison"}}]
    };
    // Create a new Pokémon object using the mock data.
    const mockPoke = new PokemonData(mockData);
    // Show the Pokémon object in #output div.
    document.getElementById("output").innerHTML = mockPoke.renderInfoTable();
}
  