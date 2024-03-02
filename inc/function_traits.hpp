/**
 * @file function_traits.hpp
 * @author Teruaki Ata (PFA03027@nifty.com)
 * @brief
 * @version 0.1
 * @date 2024-03-02
 *
 * @copyright Copyright (c) 2024, Teruaki Ata (PFA03027@nifty.com)
 *
 */

#ifndef FUNCTION_TRAITS_HPP_
#define FUNCTION_TRAITS_HPP_

#include <type_traits>

template <typename F>
struct function_traits {
private:
	// メンバー関数の型を返すメタ関数
	template <typename U = F, typename std::enable_if<std::is_member_function_pointer<U>::value>::type* = nullptr>
	static U get_invocalble_type( U );

	// クラスに定義された関数呼び出し演算子の型を返すメタ関数
	template <typename U = F, typename std::enable_if<std::is_class<U>::value>::type* = nullptr>
	static auto get_invocalble_type( U ) -> decltype( get_invocalble_type( &U::operator() ) );

	// 関数型の型を返すメタ関数（実際には、クラスでもメンバー関数型でもない場合の引数の型を返すメタ関数）
	template <typename U = F, typename std::enable_if<( !std::is_member_function_pointer<U>::value ) && ( !std::is_class<U>::value )>::type* = nullptr>
	static U get_invocalble_type( U );

	// ================================================================
	// 関数オブジェクトの引数の数を返すメタクラスの実装クラスのプライマリテンプレート
	template <typename C>
	struct get_number_of_arguments_impl {
	};

	// 部分特殊化によって定義されたメンバ関数の引数の数を返すメタクラス
	template <typename C, typename R, typename... Args>
	struct get_number_of_arguments_impl<R ( C::* )( Args... )> {
		static constexpr std::size_t value = sizeof...( Args );
		using return_type                  = R;
	};

	// 部分特殊化によって定義された定数型メンバ関数の引数の数を返すメタクラス
	template <typename C, typename R, typename... Args>
	struct get_number_of_arguments_impl<R ( C::* )( Args... ) const> {
		static constexpr std::size_t value = sizeof...( Args );
		using return_type                  = R;
	};

	// 部分特殊化によって定義された関数型の引数の数を返すメタクラス
	template <typename R, typename... Args>
	struct get_number_of_arguments_impl<R ( * )( Args... )> {
		static constexpr std::size_t value = sizeof...( Args );
		using return_type                  = R;
	};

	// 部分特殊化によって定義された関数型の引数の数を返すメタクラス
	template <typename R, typename... Args>
	struct get_number_of_arguments_impl<R ( & )( Args... )> {
		static constexpr std::size_t value = sizeof...( Args );
		using return_type                  = R;
	};

	// ================================================================
	template <std::size_t N, typename... Args>
	struct get_nth_argument {
		using type = void;
	};

	template <std::size_t N, typename HeadArg, typename... RestArgs>
	struct get_nth_argument<N, HeadArg, RestArgs...> {
		using type = typename std::conditional<N == 0, HeadArg, typename get_nth_argument<N - 1, RestArgs...>::type>::type;
	};

	// ================================================================
	// 関数オブジェクトの引数型を返すメタクラスの実装クラスのプライマリテンプレート
	template <std::size_t N, typename C>
	struct get_type_of_argument_impl {
	};

	// 部分特殊化によって定義されたメンバ関数の引数型を返すメタクラス
	template <std::size_t N, typename C, typename R, typename... Args>
	struct get_type_of_argument_impl<N, R ( C::* )( Args... )> {
		using type = typename get_nth_argument<N, Args...>::type;
	};

	// 部分特殊化によって定義された定数型メンバ関数の引数型を返すメタクラス
	template <std::size_t N, typename C, typename R, typename... Args>
	struct get_type_of_argument_impl<N, R ( C::* )( Args... ) const> {
		using type = typename get_nth_argument<N, Args...>::type;
	};

	// 部分特殊化によって定義された関数型の引数型を返すメタクラス
	template <std::size_t N, typename R, typename... Args>
	struct get_type_of_argument_impl<N, R ( * )( Args... )> {
		using type = typename get_nth_argument<N, Args...>::type;
	};

	// 部分特殊化によって定義された関数型の引数型を返すメタクラス
	template <std::size_t N, typename R, typename... Args>
	struct get_type_of_argument_impl<N, R ( & )( Args... )> {
		using type = typename get_nth_argument<N, Args...>::type;
	};

public:
	using function_type = decltype( get_invocalble_type( std::declval<F>() ) );

	using return_type = typename get_number_of_arguments_impl<function_type>::return_type;

	template <std::size_t N>
	using nth_argument_type = typename get_type_of_argument_impl<N, function_type>::type;

	static constexpr std::size_t size_of_args = get_number_of_arguments_impl<function_type>::value;
};

#endif
