# 3.11.10 Program to Create a Bitcoin Transaction and Sign It with senders private key
# Using the bitcoinlib Library

from bitcoinlib.transactions import Transaction
from bitcoinlib.keys import Key

print("Bitcoin UTXO Transaction Signing\n")

# Sender's private key
sender_private_key = Key()

# Sender and receiver addresses
sender_address = sender_private_key.address()
receiver_address = "1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa"

# Existing UTXO being spent
previous_transaction_id = "1" * 64
previous_output_index = 0
previous_utxo_value = 150000

# Transaction amounts
receiver_amount = 100000
mining_fee = 1000

# Calculate sender's change
sender_change = (
    previous_utxo_value
    - receiver_amount
    - mining_fee
)

if sender_change < 0:
    raise ValueError("Insufficient UTXO value")

# Create transaction
bitcoin_transaction = Transaction()

# Add UTXO as transaction input
bitcoin_transaction.add_input(
    prev_txid=previous_transaction_id,
    output_n=previous_output_index
)

# Add receiver output
bitcoin_transaction.add_output(
    address=receiver_address,
    value=receiver_amount
)

# Add change output
if sender_change > 0:
    bitcoin_transaction.add_output(
        address=sender_address,
        value=sender_change
    )

# Sign transaction with sender's private key
bitcoin_transaction.sign(sender_private_key)

# Display transaction information
print("Transaction Details")
print("-------------------")
print("Sender Address       :", sender_address)
print("Receiver Address     :", receiver_address)

print("\nInput UTXO")
print("Previous TXID        :", previous_transaction_id)
print("Previous Output Index:", previous_output_index)
print("UTXO Value           :", previous_utxo_value, "satoshi")

print("\nTransaction Outputs")
print("Receiver Amount      :", receiver_amount, "satoshi")
print("Change Amount        :", sender_change, "satoshi")
print("Mining Fee           :", mining_fee, "satoshi")

print("\nValue Verification")
print("Input Value          :", previous_utxo_value, "satoshi")
print("Output Value         :", receiver_amount + sender_change, "satoshi")
print("Mining Fee           :", mining_fee, "satoshi")

print("\nSigned Transaction Hex")
print(bitcoin_transaction.raw_hex())