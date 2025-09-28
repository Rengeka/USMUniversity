const filePath = 'transactions.json';

/**
 * Represents a transaction.
 * @class
 */
class Transaction {
    /**
     * Create a Transaction object.
     * @constructor
     * @param {number} id - The transaction ID.
     * @param {string} date - The transaction date.
     * @param {number} amount - The transaction amount.
     * @param {string} category - The transaction category.
     * @param {string} description - The transaction description.
     */
    constructor(id, date, amount, category, description) {
        this.id = id;
        this.date = date;
        this.amount = amount;
        this.category = category;
        this.description = description;
    }
}

/**
 * Displays transaction data in a specified container.
 * @param {Transaction} transaction - The transaction to display.
 */
function ShowTransactionData(transaction) {
    const dataContainer = document.getElementById('transaction-data');
    console.log(dataContainer)
    dataContainer.textContent = `ID: ${transaction.id}, Дата: ${transaction.date}, Сумма: ${transaction.amount}, Категория: ${transaction.category}, Описание: ${transaction.description}`;
}

/**
 * Counts the total amount of transactions.
 * @returns {number} - The total amount.
 */
function CountTotal(){
    let total = 0;
    transactions.forEach(transaction => {
        total += transaction.amount;
    })

    return total;
}

/**
 * Creates a new transaction and adds it to the list.
 */
function CreateTransaction(){
    const amount = document.getElementById('amount').value;
    const category = document.getElementById('category').value;
    const description = document.getElementById('description').value;

    const today = new Date();
    const todayDate = `${today.getFullYear()}-${today.getMonth() + 1}-${today.getDate()}`;

    const transaction = {
        amount: Number(amount),
        category: category,
        description: description,
        date: todayDate,
        id: Number(transactions[transactions.length - 1].id + 1)
    };

    transactions.push(transaction);
    AddTransaction(transaction);

    document.getElementById('amount').value = '';
    document.getElementById('description').value = '';
}

/**
 * Updates the total amount displayed.
 */
function UpdateTotal(){
    const h1 = document.getElementById("total");
    h1.innerText = " Total : " + CountTotal();
}
const table = document.getEleФайmentById('transaction-table');


/**
 * Adds event listener to the transaction table for showing transaction data.
 */
table.addEventListener('click', (event) => {
    const id = event.target.closest("tr").id;
    ShowTransactionData(transactions.find((transaction) => transaction.id == id));
});

/**
 * Adds a transaction to the table.
 * @param {Transaction} tran - The transaction to add.
 */
function AddTransaction(tran) {
    AddTransactionToTable(tran, table);
    UpdateTotal();
}

/**
 * Deletes a transaction from the list and table.
 * @param {number} ID - The ID of the transaction to delete.
 */
function DeleteTransaction(ID) {
    const table = document.getElementById('transaction-table');
    const rows = table.getElementsByTagName('tr');

    for (let i = 1; i < rows.length; i++) {
        const row = rows[i];
        const idCell = row.getElementsByTagName('td')[0];

        if (idCell.textContent === ID.toString()) {
            table.removeChild(row);
            transactions = transactions.filter(tran => tran.id !== ID);
            break;
        }
    }

    UpdateTotal();
}

/**
 * Adds a transaction row to the table.
 * @param {Transaction} tran - The transaction to add.
 * @param {HTMLTableElement} table - The table element.
 */
function AddTransactionToTable(tran, table) {
    let tr = document.createElement("tr");

    if (tran.amount > 0) {
        tr.style.backgroundColor = 'green';
    } else {
        tr.style.backgroundColor = 'red';
    }

    let td1 = document.createElement("td");
    let td2 = document.createElement("td");
    let td3 = document.createElement("td");
    let td4 = document.createElement("td");
    let td5 = document.createElement("td");

    tr.id = tran.id.toString();
    td1.textContent = tran.id.toString();
    td2.textContent = tran.date;
    td3.textContent = tran.category;
    td4.textContent = tran.description;

    let btn = document.createElement("button");
    btn.textContent = "Удалить";
    btn.addEventListener('click', function() {
        DeleteTransaction(tran.id);
    });

    td5.appendChild(btn)

    tr.appendChild(td1);
    tr.appendChild(td2);
    tr.appendChild(td3);
    tr.appendChild(td4);
    tr.appendChild(td5);

    table.appendChild(tr);
}

/** @type {Transaction[]} */
let transactions = [];

/**
 * Loads transactions from a JSON file.
 */
async function LoadTransactions() {
    try {
        const response = await fetch(filePath);
        const data = await response.json();
        console.log('Loaded data:', data);

        if (Array.isArray(data.transactions)) {
            transactions = data.transactions.map(transaction => new Transaction(transaction.id, transaction.date, transaction.amount, transaction.category, transaction.description));

            const table = document.getElementById('transaction-table');
            transactions.forEach(tran => {
                AddTransactionToTable(tran, table);
            });

            UpdateTotal();
        } else {
            console.error('Data loaded does not contain a transactions array.');
        }

    } catch (error) {
        console.error('Error loading transactions:', error);
    }
}

LoadTransactions();