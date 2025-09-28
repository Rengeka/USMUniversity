/**
 * Function to get a random activity
 * @returns {Promise<string>} A promise that resolves with a random activity.
 * @throws {Error} If network response was not ok.
 */
export function getRandomActivity()
{
    return fetch('https://www.boredapi.com/api/activity/')
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.json();
        })
        .then(data => {
            return data.activity;
        });
}

/**
 * Asynchronously gets a random activity
 * @returns {Promise<string>} A promise that resolves with a random activity.
 * @throws {Error} If there is an error fetching the activity.
 */
export async function getRandomActivityAsync() {
    try {
        const response = await fetch('https://www.boredapi.com/api/activity/');
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        const data = await response.json();
        return data.activity;
    } catch (error) {
        throw new Error('Error fetching activity:', error);
    }
}
