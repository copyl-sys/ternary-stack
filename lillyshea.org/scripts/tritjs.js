// tritjs.js - Ternary Logic Adapter for Lilly Shea Distro
const TritJS = (function () {
  const tritToBin = { 0: 0b00, 1: 0b01, 2: 0b10 };
  const binToTrit = { 0: 0, 1: 1, 2: 2 };

  function tritsToBinary(trits) {
    return trits.reduce((acc, trit) => (acc << 2) | tritToBin[trit], 0);
  }

  function binaryToTrits(bin, length) {
    const trits = [];
    for (let i = 0; i < length; i++) {
      trits.unshift(binToTrit[bin & 0b11]);
      bin >>= 2;
    }
    return trits;
  }

  function tritAdd(a, b) {
    const sum = a + b;
    return { value: sum % 3, carry: Math.floor(sum / 3) };
  }

  return {
    add: (tritsA, tritsB) => {
      const maxLen = Math.max(tritsA.length, tritsB.length);
      const paddedA = tritsA.concat(Array(maxLen - tritsA.length).fill(0));
      const paddedB = tritsB.concat(Array(maxLen - tritsB.length).fill(0));
      let carry = 0;
      const result = [];
      for (let i = maxLen - 1; i >= 0; i--) {
        const sum = tritAdd(paddedA[i] + carry, paddedB[i]);
        result.unshift(sum.value);
        carry = sum.carry;
      }
      if (carry) result.unshift(carry);
      return result;
    },
    toString: (trits) => trits.join(''),
    isTernaryNative: () => typeof navigator !== 'undefined' && !!navigator.tritSupport
  };
})();