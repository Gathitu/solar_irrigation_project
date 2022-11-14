// @immutable
class Tuple<T, U, P ,L ,E> {
  final T first;
  final U second;
  final P third;
  final L fourth;
  final E fifth;
  const Tuple(this.first, this.second,this.third,this.fourth,this.fifth);

  @override
  String toString() {
    return 'FullTuple{first: $first, second: $second, third: $third, fourth: $fourth, '
        'fifth: $fifth}';
  }
}

/// Represents a 5-tuple, or quintuple.
class Tuple5<T1, T2, T3, T4, T5> {
  /// Returns the first item of the tuple
  final T1 item1;

  /// Returns the second item of the tuple
  final T2 item2;

  /// Returns the third item of the tuple
  final T3 item3;

  /// Returns the fourth item of the tuple
  final T4 item4;

  /// Returns the fifth item of the tuple
  final T5 item5;

  /// Creates a new tuple value with the specified items.
  const Tuple5(this.item1, this.item2, this.item3, this.item4, this.item5);

  /// Create a new tuple value with the specified list [items].
  factory Tuple5.fromList(List items) {
    if (items.length != 5) {
      throw ArgumentError('items must have length 5');
    }

    return Tuple5<T1, T2, T3, T4, T5>(items[0] as T1, items[1] as T2,
        items[2] as T3, items[3] as T4, items[4] as T5);
  }

  /// Returns a tuple with the first item set to the specified value.
  Tuple5<T1, T2, T3, T4, T5> withItem1(T1 v) =>
      Tuple5<T1, T2, T3, T4, T5>(v, item2, item3, item4, item5);

  /// Returns a tuple with the second item set to the specified value.
  Tuple5<T1, T2, T3, T4, T5> withItem2(T2 v) =>
      Tuple5<T1, T2, T3, T4, T5>(item1, v, item3, item4, item5);

  /// Returns a tuple with the third item set to the specified value.
  Tuple5<T1, T2, T3, T4, T5> withItem3(T3 v) =>
      Tuple5<T1, T2, T3, T4, T5>(item1, item2, v, item4, item5);

  /// Returns a tuple with the fourth item set to the specified value.
  Tuple5<T1, T2, T3, T4, T5> withItem4(T4 v) =>
      Tuple5<T1, T2, T3, T4, T5>(item1, item2, item3, v, item5);

  /// Returns a tuple with the fifth item set to the specified value.
  Tuple5<T1, T2, T3, T4, T5> withItem5(T5 v) =>
      Tuple5<T1, T2, T3, T4, T5>(item1, item2, item3, item4, v);

  /// Creates a [List] containing the items of this [Tuple5].
  ///
  /// The elements are in item order. The list is variable-length
  /// if [growable] is true.
  List toList({bool growable = false}) =>
      List.from([item1, item2, item3, item4, item5], growable: growable);

  @override
  String toString() => '[$item1, $item2, $item3, $item4, $item5]';

  @override
  bool operator ==(Object other) =>
      other is Tuple5 &&
      other.item1 == item1 &&
      other.item2 == item2 &&
      other.item3 == item3 &&
      other.item4 == item4 &&
      other.item5 == item5;

  @override
  int get hashCode => Object.hashAll([
        item1.hashCode,
        item2.hashCode,
        item3.hashCode,
        item4.hashCode,
        item5.hashCode
      ]);
}



class Tuple7<T1, T2, T3, T4, T5, T6, T7> {
  /// Returns the first item of the tuple
  final T1 item1;

  /// Returns the second item of the tuple
  final T2 item2;

  /// Returns the third item of the tuple
  final T3 item3;

  /// Returns the fourth item of the tuple
  final T4 item4;

  /// Returns the fifth item of the tuple
  final T5 item5;

  /// Returns the sixth item of the tuple
  final T6 item6;

  /// Returns the seventh item of the tuple
  final T7 item7;

  /// Creates a new tuple value with the specified items.
  const Tuple7(this.item1, this.item2, this.item3, this.item4, this.item5,
      this.item6, this.item7);

  /// Create a new tuple value with the specified list [items].
  factory Tuple7.fromList(List items) {
    if (items.length != 7) {
      throw ArgumentError('items must have length 7');
    }

    return Tuple7<T1, T2, T3, T4, T5, T6, T7>(
        items[0] as T1,
        items[1] as T2,
        items[2] as T3,
        items[3] as T4,
        items[4] as T5,
        items[5] as T6,
        items[6] as T7);
  }

  /// Returns a tuple with the first item set to the specified value.
  Tuple7<T1, T2, T3, T4, T5, T6, T7> withItem1(T1 v) =>
      Tuple7<T1, T2, T3, T4, T5, T6, T7>(
          v, item2, item3, item4, item5, item6, item7);

  /// Returns a tuple with the second item set to the specified value.
  Tuple7<T1, T2, T3, T4, T5, T6, T7> withItem2(T2 v) =>
      Tuple7<T1, T2, T3, T4, T5, T6, T7>(
          item1, v, item3, item4, item5, item6, item7);

  /// Returns a tuple with the third item set to the specified value.
  Tuple7<T1, T2, T3, T4, T5, T6, T7> withItem3(T3 v) =>
      Tuple7<T1, T2, T3, T4, T5, T6, T7>(
          item1, item2, v, item4, item5, item6, item7);

  /// Returns a tuple with the fourth item set to the specified value.
  Tuple7<T1, T2, T3, T4, T5, T6, T7> withItem4(T4 v) =>
      Tuple7<T1, T2, T3, T4, T5, T6, T7>(
          item1, item2, item3, v, item5, item6, item7);

  /// Returns a tuple with the fifth item set to the specified value.
  Tuple7<T1, T2, T3, T4, T5, T6, T7> withItem5(T5 v) =>
      Tuple7<T1, T2, T3, T4, T5, T6, T7>(
          item1, item2, item3, item4, v, item6, item7);

  /// Returns a tuple with the sixth item set to the specified value.
  Tuple7<T1, T2, T3, T4, T5, T6, T7> withItem6(T6 v) =>
      Tuple7<T1, T2, T3, T4, T5, T6, T7>(
          item1, item2, item3, item4, item5, v, item7);

  /// Returns a tuple with the seventh item set to the specified value.
  Tuple7<T1, T2, T3, T4, T5, T6, T7> withItem7(T7 v) =>
      Tuple7<T1, T2, T3, T4, T5, T6, T7>(
          item1, item2, item3, item4, item5, item6, v);

  /// Creates a [List] containing the items of this [Tuple5].
  ///
  /// The elements are in item order. The list is variable-length
  /// if [growable] is true.
  List toList({bool growable = false}) =>
      List.from([item1, item2, item3, item4, item5, item6, item7],
          growable: growable);

  @override
  String toString() =>
      '[$item1, $item2, $item3, $item4, $item5, $item6, $item7]';

  @override
  bool operator ==(Object other) =>
      other is Tuple7 &&
      other.item1 == item1 &&
      other.item2 == item2 &&
      other.item3 == item3 &&
      other.item4 == item4 &&
      other.item5 == item5 &&
      other.item6 == item6 &&
      other.item7 == item7;

  @override
  int get hashCode => Object.hashAll([
        item1.hashCode,
        item2.hashCode,
        item3.hashCode,
        item4.hashCode,
        item5.hashCode,
        item6.hashCode,
        item7.hashCode
      ]);
}