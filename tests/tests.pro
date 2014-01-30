###################################################################################################
#                                                                                                 #
#   OpenNN: Open Neural Networks Library                                                          #
#   www.intelnics.com/opennn                                                                      #
#                                                                                                 #
#   T E S T S   P R O J E C T                                                                     #
#                                                                                                 #
#   Roberto Lopez                                                                                 #
#   Intelnics - The artificial intelligence company                                               #
#   robertolopez@intelnics.com                                                                    #
#                                                                                                 #
###################################################################################################

QT = # Do not use Qt

CONFIG += console

TARGET = opennntests

TEMPLATE = app

DESTDIR = "$$PWD\bin"

SOURCES += \
    unit_testing.cpp \
    variables_test.cpp \
    instances_test.cpp \
    data_set_test.cpp \
    plug_in_test.cpp \
    ordinary_differential_equations_test.cpp \
    mathematical_model_test.cpp \
    unscaling_layer_test.cpp \
    scaling_layer_test.cpp \
    probabilistic_layer_test.cpp \
    perceptron_layer_test.cpp \
    perceptron_test.cpp \
    neural_network_test.cpp \
    multilayer_perceptron_test.cpp \
    inputs_test.cpp \
    outputs_test.cpp \
    independent_parameters_test.cpp \
    conditions_layer_test.cpp \
    bounding_layer_test.cpp \
    sum_squared_error_test.cpp \
    root_mean_squared_error_test.cpp \
    solutions_error_test.cpp \
    performance_term_test.cpp \
    mock_performance_term.cpp \
    performance_functional_test.cpp \
    outputs_integrals_test.cpp \
    normalized_squared_error_test.cpp \
    neural_parameters_norm_test.cpp \
    minkowski_error_test.cpp \
    mean_squared_error_test.cpp \
    inverse_sum_squared_error_test.cpp \
    independent_parameters_error_test.cpp \
    final_solutions_error_test.cpp \
    cross_entropy_error_test.cpp \
    training_strategy_test.cpp \
    training_rate_algorithm_test.cpp \
    mock_training_algorithm.cpp \
    training_algorithm_test.cpp \
    random_search_test.cpp \
    quasi_newton_method_test.cpp \
    newton_method_test.cpp \
    levenberg_marquardt_algorithm_test.cpp \
    gradient_descent_test.cpp \
    evolutionary_algorithm_test.cpp \
    conjugate_gradient_test.cpp \
    testing_analysis_test.cpp \
    vector_test.cpp \
    matrix_test.cpp \
    numerical_integration_test.cpp \
    numerical_differentiation_test.cpp \
    linear_algebraic_equations_test.cpp \
    model_selection_test.cpp \
    main.cpp

HEADERS += \
    unit_testing.h \
    variables_test.h \
    instances_test.h \
    data_set_test.h \
    plug_in_test.h \
    ordinary_differential_equations_test.h \
    mathematical_model_test.h \
    unscaling_layer_test.h \
    scaling_layer_test.h \
    probabilistic_layer_test.h \
    perceptron_layer_test.h \
    perceptron_test.h \
    neural_network_test.h \
    multilayer_perceptron_test.h \
    inputs_test.h \
    outputs_test.h \
    independent_parameters_test.h \
    conditions_layer_test.h \
    bounding_layer_test.h \
    sum_squared_error_test.h \
    root_mean_squared_error_test.h \
    solutions_error_test.h \
    performance_term_test.h \
    mock_performance_term.h \
    performance_functional_test.h \
    outputs_integrals_test.h \
    normalized_squared_error_test.h \
    neural_parameters_norm_test.h \
    minkowski_error_test.h \
    mean_squared_error_test.h \
    inverse_sum_squared_error_test.h \
    independent_parameters_error_test.h \
    final_solutions_error_test.h \
    cross_entropy_error_test.h \
    training_strategy_test.h \
    training_rate_algorithm_test.h \
    mock_training_algorithm.h \
    training_algorithm_test.h \
    random_search_test.h \
    quasi_newton_method_test.h \
    newton_method_test.h \
    levenberg_marquardt_algorithm_test.h \
    gradient_descent_test.h \
    evolutionary_algorithm_test.h \
    conjugate_gradient_test.h \
    testing_analysis_test.h \
    vector_test.h \
    matrix_test.h \
    numerical_integration_test.h \
    numerical_differentiation_test.h \
    linear_algebraic_equations_test.h \
    model_selection_test.h \
    opennn_tests.h

win32{
QMAKE_LFLAGS += -static-libgcc
QMAKE_LFLAGS += -static-libstdc++
QMAKE_LFLAGS += -static
}

# OpenNN Library

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../source/release/ -lopennn
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../source/debug/ -lopennn
else:unix: LIBS += -L$$OUT_PWD/../source/ -lopennn

INCLUDEPATH += $$PWD/../source
DEPENDPATH += $$PWD/../source

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../source/release/libopennn.a
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../source/debug/libopennn.a
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../source/libopennn.a

# TinyXML2 Library

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../tinyxml2/release/ -ltinyxml2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../tinyxml2/debug/ -ltinyxml2
else:unix: LIBS += -L$$OUT_PWD/../tinyxml2/ -ltinyxml2

INCLUDEPATH += $$PWD/../tinyxml2
DEPENDPATH += $$PWD/../tinyxml2

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../tinyxml2/release/libtinyxml2.a
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../tinyxml2/debug/libtinyxml2.a
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../tinyxml2/libtinyxml2.a
