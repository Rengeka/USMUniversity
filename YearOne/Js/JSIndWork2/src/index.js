import { getRandomActivity } from './activity.js';
import { getRandomActivityAsync } from './activity.js';

/**
 * Updates the activity on the page by fetching a random activity synchronously.
 * If an error occurs during fetching, it displays an error message on the page.
 * @returns {void}
 */
function updateActivity()
{
    getRandomActivity()
        .then(activity => {
            document.getElementById('activity').textContent = activity;
            console.log(activity)
        })
        .catch(error => {
            console.error('Error fetching activity:', error);
            document.getElementById('activity').textContent = "К сожалению, произошла ошибка";
        });
}

/**
 * Updates the activity on the page by fetching a random activity asynchronously.
 * If an error occurs during fetching, it displays an error message on the page.
 * @returns {void}
 */
async function updateActivityAsync() {
    try {
        const activity = await getRandomActivityAsync(); // Получаем активность
        document.getElementById('activity').textContent = activity; // Отображаем активность на странице
    } catch (error) {
        console.error('Error updating activity:', error);
        document.getElementById('activity').textContent = "К сожалению, произошла ошибка";
    }
}

/*updateActivity();
setInterval(updateActivity, 1000);*/

updateActivityAsync();
setInterval(updateActivityAsync, 1000);