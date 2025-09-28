<?php

declare(strict_types=1);

$transactions = [
    [
        "id" => 1,
        "date" => "2019-01-01",
        "amount" => 100.00,
        "description" => "Payment for groceries",
        "merchant" => "SuperMart",
    ],
    [
        "id" => 2,
        "date" => "2020-02-15",
        "amount" => 75.50,
        "description" => "Dinner with friends",
        "merchant" => "Local Restaurant",
    ],
];

/**
 * Function to create and add new transaction in array of transactions
 * 
 * @param int $id - transaction's id
 * @param string $date - transaction commiting date
 * @param string $amount - a money amount that was processed by transaction
 * @param string $description - transaction's description
 * @param string $merchant - transaction commiting date
 */
function addTransaction(int $id, string $date, float $amount, string $description, string $merchant): void {
    global $transactions;

    $transaction = [
        "id" => $id,
        "date" => $date,
        "amount" => $amount,
        "description" => $description,
        "merchant" => $merchant,
    ];

    $transactions.array_push($transaction);
}

/**
 * Function to calculate the sum of amount of all transactions
 * 
 * @param array $transactions - an array of transaction to calculate total ammount
 * 
 * @return float sum of amounts
 */
function calculateTotalAmount(array $transactions): float{
    return array_sum(array_column($transactions, 'amount'));
}

/**
 * Function to find a transaction by description
 * 
 * @param string $descriptionPart - description of searched transaction
 * 
 * @return array transaction
 */
function findTransactionByDescription(string $descriptionPart){
    global $transactions;
    return array_find($transactions, fn($t) => $t['description'] === $descriptionPart );
}


/**
 * Function to find a transaction by id
 * 
 * @param int $id - id of searched  transaction
 * 
 * @return array transaction
 */
function findTransactionById(int $id){
    global $transactions;
    
    foreach ($transactions as $transaction){
        if($transaction['id'] === $id){
            return $transaction;
        }
    };
}

/**
 * Function to find a transaction by id using array_filter
 * 
 * @param int $id - id of searched  transaction
 * 
 * @return array transaction
 */
function findTransactionByIdWithFilter(int $id){
    global $transactions;
    
    return array_filter($transactions, fn($t) => $t['id'] === $id);
}

usort($transactions, fn($tr1, $tr2) => $tr1['date'] <=> $tr2['date']);
usort($transactions, fn($tr1, $tr2) => $tr2['amount'] <=> $tr1['amount']);

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
<table border='1'>
    <thead>
        <tr>
            <th>id</th>
            <th>date</th>
            <th>amount</th>
            <th>description</th>
            <th>merchant</th>
        </tr>
    </thead>
    <tbody>
        <?php foreach ($transactions as $transaction) { ?>
            <tr>
                <td><?php echo $transaction['id']; ?></td>
                <td><?php echo $transaction['date']; ?></td>
                <td><?php echo $transaction['amount']; ?></td>
                <td><?php echo $transaction['description']; ?></td>
                <td><?php echo $transaction['merchant']; ?></td>
            </tr>
        <?php } ?>
    </tbody>
</table>
</body>
</html>