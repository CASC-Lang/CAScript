export {};

declare global {
	export interface Map<K, V> {
		find(predicate: (key: K) => boolean): Entry<K, V>;
	}
}

class Entry<K, V> {
	public readonly key: K;
	public readonly value: V;

	constructor(key: K, value: V) {
		this.key = key;
		this.value = value;
	}
}

Map.prototype.find = function <K, V>(
	this: Map<K, V>,
	predicate: (key: K) => boolean
): Entry<K, V> {
    let result = undefined;

	this.forEach((v, k) => {
		if (predicate(k)) result = new Entry(k, v);
	});

	return result;
};
