package csl.candidateExtractor;

public interface CandidateReceiver {
    public abstract void receive( String str, float levDistance, float frequency );
}
