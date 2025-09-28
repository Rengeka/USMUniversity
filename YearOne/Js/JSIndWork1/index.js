
/**
 JS DOCS?*/
class TransactionAnalyzer
{
    /**
     * Creates an instance of TransactionAnalyzer.
     */
    constructor()
    {
        this._transactions = this.ParseTransactions();
    }

    /**
     * Add a transaction to the list of transactions.
     * @param {Object} transaction - The transaction object to add.
     */
    addTransaction(transaction)
    {
        this._transactions.push(transaction)
    }

    /**
     * Get all transactions.
     * @returns {Array} - Array of transactions.
     */
    getAllTransaction()
    {
        return this._transactions;
    }

    /**
     * Parse transactions from a JSON file.
     * @returns {Array} - Array of parsed transactions.
     */
    ParseTransactions()
    {
        const fs = require('fs');
        const filePath = 'C:\\Users\\stasi\\WebstormProjects\\individualwork\\Conditions\\transaction.json';

        const data = fs.readFileSync(filePath, 'utf8');
        const transactions = JSON.parse(data);
        return transactions;
    }

    /**
     * Get unique transaction types.
     * @returns {Set} - Set of unique transaction types.
     */
    getUniqueTransactionType()// I
    {
        const types = new Set();

        for (const transaction of this._transactions)
        {
            types.add(transaction.transaction_type);
        }

        return types;
    }

    /**
     * Calculate the total amount of all transactions.
     * @returns {number} - Total amount of transactions.
     */
    calculateTotalAmount() // II
    {
        /*return this._transactions.length;*/

        let midAmmount = 0;

        this._transactions.forEach(transaction => {
            midAmmount += transaction.transaction_amount;
        });

        return midAmmount;
    }

    /**
     * Calculate the total amount of transactions for a specific date.
     * @param {number} year - The year of the date.
     * @param {number} month - The month of the date.
     * @param {number} day - The day of the date.
     * @returns {number} - Total amount of transactions for the specified date.
     */
    calculateTotalAmountByDate(year, month, day) // III
    {

        let targetDate = '';

        if (year !== undefined) {
            targetDate += year;
        }
        if (month !== undefined) {
            targetDate += '-' + month;
        }
        if (day !== undefined) {
            targetDate += '-' + day;
        }

        const transactionsWithTargetDate = this._transactions.filter(transaction => {
            return targetDate === '' || transaction.transaction_date.startsWith(targetDate);
        });

        let totalAmmount = 0;

        transactionsWithTargetDate.forEach(transaction => {
            totalAmmount += transaction.transaction_amount;
        });

        return totalAmmount;
    }

    /**
     * Get transactions of a specific type.
     * @param {string} type - The type of transaction.
     * @returns {Array} - Array of transactions of the specified type.
     */
    getTransactionByType(type) // IV
    {
        const transactions = this._transactions.filter(transaction => {
            return transaction.transaction_type === type;
        });

        return transactions;
    }

    /**
     * Get transactions within a specified date range.
     * @param {string} startDate - The start date of the range.
     * @param {string} endDate - The end date of the range.
     * @returns {Array} - Array of transactions within the specified date range.
     */
    getTransactionsInDateRange(startDate, endDate) // V
    {
        const transactions = this._transactions.filter(transaction => {
            return transaction.transaction_date <= endDate && transaction.transaction_date >= startDate;
        });

        return transactions;
    }

    /**
     * Get transactions by merchant name.
     * @param {string} merchantName - The name of the merchant.
     * @returns {Array} - Array of transactions from the specified merchant.
     */
    getTransactionsByMerchant(merchantName) // VI
    {
        const transactions = this._transactions.filter(transaction => {
            return transaction.merchant_name === merchantName;
        });

        return transactions;
    }

    /**
     * Calculate the average transaction amount.
     * @returns {number} - The average transaction amount.
     */
    calculateAverageTransactionAmount() // VII
    {
        let midAmmount = 0;

        this._transactions.forEach(transaction => {
            midAmmount += transaction.transaction_amount;
        });

        return midAmmount/this._transactions.length;
    }

    /**
     * Get transactions within a specified amount range.
     * @param {number} minAmount - The minimum amount of the range.
     * @param {number} maxAmount - The maximum amount of the range.
     * @returns {Array} - Array of transactions within the specified amount range.
     */
    getTransactionsByAmountRange(minAmount, maxAmount) // VIII
    {
        const transactions = this._transactions.filter(transaction => {
            return transaction.transaction_amount >= minAmount && transaction.transaction_amount <= maxAmount;
        });

       return transactions;
    }

    /**
     * Calculate the total debit amount.
     * @returns {number} - Total debit amount.
     */
    calculateTotalDebitAmount()// IX
    {
        let totalAmmount = 0;

        this._transactions.forEach(transaction => {
            if(transaction.transaction_type === "debit")
            {
                totalAmmount += transaction.transaction_amount;
            };
        });

        return totalAmmount;
    }

    /**
     * Find the month with the most transactions.
     * @returns {number} - The month with the most transactions.
     */
    findMostTransactionsMonth() // X
    {
        let ammounts = [];

        for (let i = 1; i <= 12; i++)
        {
            const transactionsWithTargetDate = this._transactions.filter(transaction => {
                return Number(transaction.transaction_date.slice(5,7)) == i;
            });

            ammounts.push(transactionsWithTargetDate.length)
        }


        return ammounts.indexOf(Math.max.apply(null, ammounts)) + 1;
    }

    /**
     * Find the month with the most debit transactions.
     * @returns {number} - The month with the most debit transactions.
     */
    findMostDebitTransactionMonth() // XI
    {
        let ammounts = [];

        const debitTransactions = this._transactions.filter(transaction => {
            return transaction.transaction_type === "debit";
        });

        for (let i = 1; i <= 12; i++)
        {
            const transactionsWithTargetDate = debitTransactions.filter(transaction => {
                return Number(transaction.transaction_date.slice(5,7)) == i;
            });

            ammounts.push(transactionsWithTargetDate.length)
        }

        return  ammounts.indexOf(Math.max.apply(null, ammounts)) + 1;
    }

    /**
     * Determine the transaction type with the most occurrences.
     * @returns {string} - The transaction type with the most occurrences ('debit', 'credit', or 'equal').
     */
    mostTransactionTypes() // XII
    {
        const debitTransactions = this._transactions.filter(transaction => {
            return transaction.transaction_type === "debit";
        });

        const creditTransactions = this._transactions.filter(transaction => {
            return transaction.transaction_type === "credit";
        });

        if(debitTransactions.length > creditTransactions.length)
        {
            return "debit";
        }
        else if(debitTransactions.length < creditTransactions.length)
        {
            return "credit";
        }
        else
        {
            return "equal";
        }
    }

    /**
     * Get transactions before a specified date.
     * @param {string} date - The target date.
     * @returns {Array} - Array of transactions before the specified date.
     */
    getTransactionsBeforeDate(date) // XIII
    {
        const transactionsBeforeTargetDate = this._transactions.filter(transaction => {
            return transaction.transaction_date <= date;
        });

        return transactionsBeforeTargetDate;
    }

    /**
     * Find a transaction by its ID.
     * @param {string} id - The ID of the transaction.
     * @returns {Object|null} - The transaction object if found, otherwise null.
     */
    findTransactionById(id) // XIV
    {
        return this._transactions.find(transaction => transaction.transaction_id == id)
    }

    /**
     * Map transaction descriptions to an array.
     * @returns {Array} - Array of transaction descriptions.
     */
    mapTransactionDescriptions() // XV
    {
        let descriptions = [];
        this._transactions.forEach(transaction => {
            descriptions.push(transaction.transaction_description)
        });

        return descriptions;
    }
}

const trAnlyzer = new TransactionAnalyzer();
console.log(trAnlyzer.getUniqueTransactionType());
console.log(trAnlyzer.calculateTotalAmount());
console.log(trAnlyzer.calculateTotalAmountByDate("2019", "04",  "30"));
console.log(trAnlyzer.getTransactionByType("debit"));
console.log(trAnlyzer.getTransactionsInDateRange("2019-04-20", "2019-04-25"));
console.log(trAnlyzer.getTransactionsByMerchant("SandwichShopXYZ"));
console.log(trAnlyzer.calculateAverageTransactionAmount());
console.log(trAnlyzer.getTransactionsByAmountRange(30, 60));
console.log(trAnlyzer.calculateTotalDebitAmount());
console.log(trAnlyzer.findMostTransactionsMonth());
console.log(trAnlyzer.findMostDebitTransactionMonth());
console.log(trAnlyzer.mostTransactionTypes());
console.log(trAnlyzer.getTransactionsBeforeDate("2019-01-03"));
console.log(trAnlyzer.findTransactionById(1));
console.log(trAnlyzer.mapTransactionDescriptions());



