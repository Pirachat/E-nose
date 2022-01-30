import pickle
import Orange
from micromlgen import port

with open(r'/orange_model/lr.pkcls', 'rb') as model:
    clf = pickle.load(model)

with open(r"/orange_model/lr_model.h", 'w') as f:
    f.write(port(clf.skl_model, classmap={0: "background", 1: "lighter", 2: "cigarette", 3: "insecticide",  4: "rotten", 5: "al", 6: "pipe" }))
# >> LogisticRegressionClassifier(skl_model=LogisticRegression(C=1,
#                                 class_weight=None, dual=False,
#                                 fit_intercept=True, intercept_scaling=1.0,
#                                 l1_ratio=None, max_iter=10000,
#                                 multi_class='auto', n_jobs=1, penalty='l2',
#                                 random_state=0, solver='lbfgs', tol=0.0001,
#                                 verbose=0, warm_start=False))


