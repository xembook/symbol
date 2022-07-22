import "transaction.cats"

# Shared content between HashLockTransaction and EmbeddedHashLockTransaction.
inline struct HashLockTransactionBody
	# Locked mosaic.
	mosaic = UnresolvedMosaic

	# Number of blocks for which a lock should be valid.
	#
	# The default maximum is 48h (See the `maxHashLockDuration` network property).
	duration = BlockDuration

	# Hash of the AggregateBondedTransaction to be confirmed before unlocking the mosaics.
	hash = Hash256


#
# \note It is not necessary to sign the aggregate and its HashLockTransaction with the same account.
# For example, if Bob wants to announce an aggregate and does not have enough funds to announce a HashLockTransaction,
# he can ask Alice to announce the lock transaction for him by sharing the signed AggregateTransaction hash.
struct HashLockTransaction
	TRANSACTION_VERSION = make_const(uint8, 1)
	TRANSACTION_TYPE = make_const(TransactionType, HASH_LOCK)

	inline Transaction
	inline HashLockTransactionBody

# Embedded version of HashLockTransaction.
struct EmbeddedHashLockTransaction
	TRANSACTION_VERSION = make_const(uint8, 1)
	TRANSACTION_TYPE = make_const(TransactionType, HASH_LOCK)

	inline EmbeddedTransaction
	inline HashLockTransactionBody
