#include "mv_discrimhist_processor.h"
#include "mv_discrimhist.h"

class mv_discrimhist_ProcessorPrivate
{
public:
    mv_discrimhist_Processor *q;
};

mv_discrimhist_Processor::mv_discrimhist_Processor() {
    d=new mv_discrimhist_ProcessorPrivate;
    d->q=this;

    this->setName("mv_discrimhist");
    this->setVersion("0.1");
    this->setInputFileParameters("timeseries","firings");
    this->setOutputFileParameters("output");
    this->setRequiredParameters("clusters");
}

mv_discrimhist_Processor::~mv_discrimhist_Processor() {
    delete d;
}

bool mv_discrimhist_Processor::check(const QMap<QString, QVariant> &params)
{
    if (!this->checkParameters(params)) return false;
    return true;
}

bool mv_discrimhist_Processor::run(const QMap<QString, QVariant> &params)
{
    QString timeseries_path=params["timeseries"].toString();
    QString firings_path=params["firings"].toString();
    QString output_path=params["output"].toString();
    QStringList clusters_strlist=params["clusters"].toString().split(",",QString::SkipEmptyParts);
    QList<int> clusters;
    foreach (QString cluster_str,clusters_strlist) {
        clusters << cluster_str.trimmed().toInt();
    }

    mv_discrimhist_opts opts;
    opts.clusters=clusters;
    return mv_discrimhist(timeseries_path,firings_path,output_path,opts);
}

