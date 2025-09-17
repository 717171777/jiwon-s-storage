export function simpleSort(arr: number[], order: 'asc' | 'desc' = 'asc'): number[] {
  const sortedArr = [...arr];

  if (sortedArr.length <= 1) {
    return sortedArr;
  }

  for (let i = 0; i < sortedArr.length - 1; i++) {
    for (let j = 0; j < sortedArr.length - 1 - i; j++) {
      const isAsc = order === 'asc';
      const shouldSwap = isAsc
        ? sortedArr[j] > sortedArr[j + 1]
        : sortedArr[j] < sortedArr[j + 1];

      if (shouldSwap) {
        // Swap elements
        const temp = sortedArr[j];
        sortedArr[j] = sortedArr[j + 1];
        sortedArr[j + 1] = temp;
      }
    }
  }

  return sortedArr;
}