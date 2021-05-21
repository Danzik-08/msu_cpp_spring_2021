template<typename First, typename Second, typename Third>
template <class Serializer>
Error Data<First, Second, Third>::serialize(Serializer& serializer) {
  return serializer(a, b, c);
}
