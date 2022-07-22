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


# it waits to be fully signed. To avoid spam attacks a HashLockTransaction must be announced and confirmed
# before an AggregateBondedTransaction can be announced. The HashLockTransaction locks a certain amount of funds


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
