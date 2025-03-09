async function pokeAPIGet(endpoint, params = "") {
    // Base URL for PokéAPI
    const baseUrl = "https://pokeapi.co/api/v2/";
    let url = baseUrl + endpoint;
    if (params !== "") { url += "?" + params;}

    // Return the fetch promise so that the caller can handle the response
    return fetch(url)
        .then((response) => {
        if (!response.ok) {
            throw new Error("Network response was not OK");
        }
        return response.json();
        })
        .catch((error) => {
        console.error("There has been a problem with your fetch operation:", error);
        throw error; // Re-throw error so that the caller can handle it
        });
}  